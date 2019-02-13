#include "GateServer.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "log/Log.h"
#include "define.h"
#include "handle/gate/WakeHeartbeat.h"
#include "handle/gate/DelSession.h"
#include "protocol/protobuf/proto_cpp/service.pb.h"

GateContext::GateContext(unsigned long long conn_seq_id)
	:	_conn_seq_id(conn_seq_id), 
		_create_time(0), 
		_update_time(0), 
		_is_send_login_request(false),
		_is_send_access_key_response(false),
		_en_conn(EN_CONN_NOT_INIT_CONN),
		_is_wake_heartbeat_wait(false)
{
	_create_time = ::time(nullptr);
	_update_time = _create_time;
}

GateServer::GateServer(Proc& proc)
	:	_proc(proc), _p_tcp_server(nullptr),
		_codec(	boost::bind(&GateServer::on_message, this, _1, _2, _3), "GateServer",
		proc._config.proc.gate_server_recv_packet_len_max,
		proc._config.proc.gate_server_send_packet_len_max),
		_handle_gate(proc)
{

}

GateServer::~GateServer()
{
	if(_p_tcp_server == nullptr)
	{
		delete _p_tcp_server;
		_p_tcp_server = nullptr;
	}
}

void GateServer::start()
{
	if(_p_tcp_server == nullptr)
	{
		_p_tcp_server = new muduo::net::TcpServer(&_proc._loop, 
			muduo::net::InetAddress(_proc._config.net.gate.ip, _proc._config.net.gate.port), "GateServer");
		_p_tcp_server->setConnectionCallback(
			boost::bind(&GateServer::on_connection, this, _1));
		_p_tcp_server->setMessageCallback(
			boost::bind(&Codec::on_stream_message, &_codec, _1, _2, _3));
		_p_tcp_server->setWriteCompleteCallback(
			boost::bind(&GateServer::on_write_complete, this, _1));
		_p_tcp_server->start();

		_proc._loop.runEvery(1.0, boost::bind(&GateServer::on_check_idle, this));
	}
}

bool GateServer::send_msg(const muduo::net::TcpConnectionPtr& conn, PacketPtr& msg)
{
	if(conn)
	{
		_codec.send_stream(get_pointer(conn), msg);
		return true;
	}

	B_LOG_WARN << "conn is null, msg is lose, _msg_seq_id=" << msg->_msg_seq_id;
	return false;
}

bool GateServer::send_stream(PacketPtr& msg)
{
	if(msg->_buffer == nullptr ||  msg->_buffer_len == 0)
	{
		B_LOG_WARN	<< "_buffer=nullptr or _buffer_len=0, msg is lose, _msg_seq_id=" << msg->_msg_seq_id
					<< ", _conn_seq_id=" << msg->_conn_seq_id
					<< ", _buffer=" << msg->_buffer
					<< ", _buffer_len=" << msg->_buffer_len;
		return false;
	}

	auto it = _conn_map.find(msg->_conn_seq_id);
	if(it == _conn_map.end())
	{
		B_LOG_WARN	<< "conn_seq_id not find, msg is lose, _msg_seq_id=" << msg->_msg_seq_id
					<< ", _conn_seq_id=" << msg->_conn_seq_id;
		return false;
	}

	if(it->second)
	{
		it->second->send(msg->_buffer, msg->_buffer_len);
		return true;
	}

	B_LOG_WARN	<< "conn is null, msg is lose, _msg_seq_id=" << msg->_msg_seq_id
				<< ", _conn_seq_id=" << msg->_conn_seq_id;
	return false;
}

bool GateServer::send_stream(PacketStreamPtr& stream)
{
	if(stream->_buffer == nullptr ||  stream->_buffer_len == 0)
	{
		B_LOG_WARN	<< "_buffer=nullptr or _buffer_len=0, msg is lose, _msg_seq_id=" << stream->_packet_ptr->_msg_seq_id
					<< ", _conn_seq_id=" << stream->_packet_ptr->_conn_seq_id
					<< ", _buffer=" << stream->_buffer
					<< ", _buffer_len=" << stream->_buffer_len;
		return false;
	}

	auto it = _conn_map.find(stream->_packet_ptr->_conn_seq_id);
	if(it == _conn_map.end())
	{
		B_LOG_WARN	<< "conn_seq_id not find, msg is lose, _msg_seq_id=" << stream->_packet_ptr->_msg_seq_id
					<< ", _conn_seq_id=" << stream->_packet_ptr->_conn_seq_id;
		return false;
	}

	if(it->second)
	{
		it->second->send(stream->_buffer, stream->_buffer_len);
		return true;
	}

	B_LOG_WARN	<< "conn is null, msg is lose, _msg_seq_id=" << stream->_packet_ptr->_msg_seq_id
				<< ", _conn_seq_id=" << stream->_packet_ptr->_conn_seq_id;
	return false;
}

void GateServer::on_connection(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name() << " " 
				<< conn->peerAddress().toIpPort() << " -> " 
				<< conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");

	if(conn->connected())
	{
		if(_proc._owner.is_not_inservice())
		{
			// 服务不在上线状态时，建立新连接时则断开连接
			B_LOG_WARN << "service is not inservice, new conn is shutdown";
			conn->shutdown();
			return;
		}

		conn->setTcpNoDelay(_proc._config.proc.gate_server_no_delay);
		conn->setHighWaterMarkCallback(boost::bind(&GateServer::on_high_water_mark, this, _1, _2),
			_proc._config.proc.gate_server_high_water_mark);

		GateContext gate_context(_proc._seq.make_seq());
		conn->setContext(gate_context);
		_conn_map.insert(std::make_pair(gate_context._conn_seq_id, conn));
	}
	else
	{
		const GateContext& gate_context = boost::any_cast<const GateContext&>(conn->getContext());
		_conn_map.erase(gate_context._conn_seq_id);

		B_LOG_INFO << "conn is close, del session, _conn_seq_id=" << gate_context._conn_seq_id;
	
		// 删除连接对应的session
		DelSession* ds = new DelSession(_proc, gate_context._conn_seq_id);
		ds->del_session();
		_proc._task_msg_pool.add(ds);	// 加入定时器
	}

	// 每次建立连接/断开连接触发同步
	_proc._put_load.trigger_sync_count();
}

void GateServer::on_message(const muduo::net::TcpConnectionPtr& conn, 
							PacketPtr& packet_ptr,
							muduo::Timestamp time)
{
	if(packet_ptr->_from_service_id <= service::CLIENT_BEGIN && packet_ptr->_from_service_id >= service::CLIENT_END)
	{
		// 非客户端连接
		B_LOG_WARN	<< "shutdown, _from_service_id not in (CLIENT_BEGIN, CLIENT_END),"
					<< ", _msg_seq_id=" << packet_ptr->_msg_seq_id
					<< ", CLIENT_BEGIN=" << service::CLIENT_BEGIN
					<< ", CLIENT_END=" << service::CLIENT_END
					<< ", _from_service_id=" << packet_ptr->_from_service_id;
		conn->shutdown();
		return;
	}

	GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
	if(p_gate_context->_en_conn == GateContext::EN_CONN_LOGIN)
	{
		if(packet_ptr->_to_service_id > service::LOGIC_BEGIN && packet_ptr->_to_service_id < service::PROXY_END)
		{
			// 只能访问业务逻辑服务和业务代理服务
			if(packet_ptr->_conn_seq_id == p_gate_context->_conn_seq_id)
			{
				// 转发请求到内部服务TcpClient, s out -> c in
				_handle_gate.forward_request_to_service(conn, packet_ptr, time);
			}
			else
			{
				// 转发响应到内部服务TcpServer, s out -> s in
				_handle_gate.forward_response_to_service(conn, packet_ptr, time);
			}
		}
		else
		{
			// 核心服务只能访问gate，其他核心服务不能访问
			if(packet_ptr->_to_service_id == Define::service_id)
			{
				// 处理client发送给gate的req
				if(packet_ptr->_to_proc_id == _proc._owner._proc_id)
				{
					bool b = packet_ptr->parse();
					if(b)
					{
						int msg_type = packet_ptr->_body.msg_type_case();
						switch(msg_type)
						{
						case data::Body::kMsgReq:
							{
								const ::data::MsgReq& msg_req = packet_ptr->_body.msg_req();

								B_LOG_INFO	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
											<< ", msg_type is req";

								_handle_gate.handle_request(conn, packet_ptr, time);
							}		
							break;

						case data::Body::kMsgRsp:
							B_LOG_ERROR	<< conn->name() << ", shutdown, _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
										<< ", msg_type is rsp";
							break;

						default:
							B_LOG_ERROR	<< conn->name() << ", shutdown, _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString() 
										<< ", unknow msg_type=" << msg_type;
							break;
						}
					}
					else
					{
						// 丢包
						B_LOG_ERROR << "lose packet, parse=false, _msg_seq_id=" << packet_ptr->_msg_seq_id;
					}
				}
				else
				{
					// 处理client返回gate的rsp
					TaskMsgBase* task = _proc._task_msg_pool.find(packet_ptr->_msg_seq_id);
					if(task == nullptr)
					{
						B_LOG_ERROR << "no find _msg_seq_id=" << packet_ptr->_msg_seq_id;
					}
					else
					{
						bool b = packet_ptr->parse();
						if(b)
						{
							int msg_type = packet_ptr->_body.msg_type_case();
							switch(msg_type)
							{
							case data::Body::kMsgReq:
								B_LOG_ERROR	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
											<< ", msg_type is req";
								break;

							case data::Body::kMsgRsp:
								{
									const ::data::MsgRsp& msg_rsp = packet_ptr->_body.msg_rsp();

									B_LOG_INFO	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
												<< ", msg_type is rsp" << ", code=" << msg_rsp.code() << ", info=" << msg_rsp.info();

									task->_response = packet_ptr;
									_handle_gate.handle_response(conn, task, time);
									_proc._task_msg_pool.del(packet_ptr->_msg_seq_id);
									task = nullptr;
								}
								break;

							default:
								B_LOG_ERROR	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString() 
											<< ", unknow msg_type=" << msg_type;
								break;
							}
						}
						else
						{
							// 丢包
							B_LOG_ERROR << "lose packet, parse=false, _msg_seq_id=" << packet_ptr->_msg_seq_id;
						}
					}
				}
			}
			else
			{
				// 没有权限访问非gate外的核心服务
				B_LOG_WARN	<< "shutdown, _to_service_id is not Define::service_id"
							<< ", _msg_seq_id=" << packet_ptr->_msg_seq_id
							<< ", Define::service_id=" << Define::service_id
							<< ", _to_service_id=" << packet_ptr->_to_service_id;
				conn->shutdown();
			}		
		}	
	}
	else if(p_gate_context->_en_conn == GateContext::EN_CONN_NOT_LOGIN)
	{
		// 必须是转发到登录服务
		if(packet_ptr->_to_service_id == service::LOGIN)
		{
			if(packet_ptr->_conn_seq_id == p_gate_context->_conn_seq_id)
			{
				// 请求
				if(p_gate_context->_is_send_login_request)
				{
					// 已经发送过登录请求，防止穷举
					B_LOG_WARN << "shutdown, _is_send_login_request=true, _msg_seq_id=" << packet_ptr->_msg_seq_id;
					conn->shutdown();
				}
				else
				{
					// 登录请求转发给登录服务器
					_handle_gate.forward_request_to_service(conn, packet_ptr, time);
					p_gate_context->_is_send_login_request = true;
				}
			}
			else
			{
				// 响应
				if(p_gate_context->_is_send_login_request)
				{
					if(p_gate_context->_is_send_access_key_response)
					{
						// 已经发送过access_key响应，防止穷举
						B_LOG_WARN << "shutdown, _is_send_access_key_response=true, _msg_seq_id=" << packet_ptr->_msg_seq_id;
						conn->shutdown();
					}
					else
					{
						// access_key响应转发给登录服务器
						_handle_gate.forward_response_to_service(conn, packet_ptr, time);
						p_gate_context->_is_send_access_key_response = true;
					}
				}
				else
				{
					// 客户端必须先发送登录请求才会有access_key响应
					B_LOG_WARN << "shutdown, access key rsp, _is_send_login_request=false, _msg_seq_id=" << packet_ptr->_msg_seq_id;
					conn->shutdown();
				}
			}
		}
		else
		{
			B_LOG_WARN	<< "shutdown, _to_service_id is not LOGIN"
						<< ", _msg_seq_id=" << packet_ptr->_msg_seq_id
						<< ", _to_service_id=" << packet_ptr->_to_service_id;
			conn->shutdown();
		}
	}
	else
	{
		// EN_CONN_NOT_INIT_CONN
		if(packet_ptr->_to_service_id == Define::service_id && packet_ptr->_to_proc_id == _proc._owner._proc_id)
		{
			bool b = packet_ptr->parse();
			if(b)
			{
				int msg_type = packet_ptr->_body.msg_type_case();
				switch(msg_type)
				{
				case data::Body::kMsgReq:
					{
						const ::data::MsgReq& msg_req = packet_ptr->_body.msg_req();

						B_LOG_INFO	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
									<< ", msg_type is req";

						_handle_gate.handle_request_not_init_conn(conn, packet_ptr, time);
					}		
					break;

				case data::Body::kMsgRsp:
					B_LOG_ERROR	<< conn->name() << ", shutdown, _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
								<< ", msg_type is rsp";
					conn->shutdown();
					break;

				default:
					B_LOG_ERROR	<< conn->name() << ", shutdown, _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString() 
								<< ", unknow msg_type=" << msg_type;
					conn->shutdown();
					break;
				}
			}
			else
			{
				// 丢包
				B_LOG_ERROR << "shutdown, lose packet, parse=false, _msg_seq_id=" << packet_ptr->_msg_seq_id;
				conn->shutdown();
			}
		}
		else
		{
			B_LOG_WARN	<< "shutdown, _to_service_id is not Define::service_id or _to_proc_id is not _owner._proc_id"
						<< ", _msg_seq_id=" << packet_ptr->_msg_seq_id
						<< ", _to_service_id=" << packet_ptr->_to_service_id
						<< ", _to_proc_id=" << packet_ptr->_to_proc_id
						<< ", Define::service_id=" << Define::service_id
						<< ", _owner._proc_id=" << _proc._owner._proc_id;
			conn->shutdown();
		}
	}

	p_gate_context->_update_time = ::time(nullptr);
}

void GateServer::on_write_complete(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name();

	GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
	p_gate_context->_update_time = ::time(nullptr);
}

void GateServer::on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len)
{
	B_LOG_WARN << conn->name() << " shutdown, len=" << len;

	// GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
	// p_gate_context->_update_time = ::time(nullptr);
	
	// 防止客户端只发送请求不接收响应，tcp发送缓冲区塞满，导致用户态的发送缓冲区不断增加，从而服务端内存不断增加
	conn->forceClose();		// 服务端强制关闭
}

void GateServer::on_check_idle()
{
	unsigned int t_now = ::time(nullptr);
	for(auto it = _conn_map.begin(); it != _conn_map.end();)
	{
		muduo::net::TcpConnectionPtr conn = it->second;
		if(conn)
		{
			GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
			if(p_gate_context->_en_conn == GateContext::EN_CONN_LOGIN)
			{
				if(p_gate_context->_is_wake_heartbeat_wait)
				{
					// 等待客户端心跳返回，无需处理
				}
				else if(t_now - p_gate_context->_update_time >= _proc._config.proc.gate_server_idle)
				{
					// 登录状态的空闲连接，给客户端发送心跳请求
					WakeHeartbeat* whb = new WakeHeartbeat(_proc, p_gate_context->_conn_seq_id);
					whb->wake_client(conn, p_gate_context);
					_proc._task_msg_pool.add(whb);	// 加入定时器
				}
			}
			else if(t_now - p_gate_context->_update_time >= _proc._config.proc.gate_server_idle)
			{
				// 非登录状态的空闲连接，直接断开连接
				B_LOG_ERROR << conn->name() << " is idle, shutdown"
											<< ", _conn_seq_id=" << p_gate_context->_conn_seq_id
											<< ", _en_conn=" << p_gate_context->_en_conn;
				conn->shutdown();
			}

			++it;
		}
		else
		{
			B_LOG_WARN << "conn expired";
			_conn_map.erase(it++);
		}
	}
}

bool GateServer::find(unsigned long long conn_seq_id, muduo::net::TcpConnectionPtr& conn)
{
	auto it = _conn_map.find(conn_seq_id);
	if(it != _conn_map.end())
	{
		conn = it->second;
		return true;
	}

	return false;
}

void GateServer::shutdown_all_conn()
{
	B_LOG_WARN << "start, _conn_map.size=" << _conn_map.size();
	unsigned int close_conn_count = 0;
	for(auto it = _conn_map.begin(); it != _conn_map.end();)
	{
		muduo::net::TcpConnectionPtr conn = it->second;
		if(conn)
		{
			conn->shutdown();
			++close_conn_count;
		}
	}

	B_LOG_WARN << "end, close_conn_count=" << close_conn_count;
}

unsigned int GateServer::conn_size()
{
	return _conn_map.size();
}




