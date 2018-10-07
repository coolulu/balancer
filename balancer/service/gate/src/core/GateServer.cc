#include "GateServer.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "log/Log.h"
#include "define.h"
#include "handle/gate/WakeHeartbeat.h"
#include "handle/gate/DelSession.h"

GateContext::GateContext(unsigned long long conn_seq_id)
	:	_conn_seq_id(conn_seq_id), 
		_create_time(0), 
		_update_time(0), 
		_is_client_init_conn_seq_id(false),
		_is_wake_heartbeat_wait(false)
{
	_create_time = time(nullptr);
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

		B_LOG_INFO << "conn is close, _conn_seq_id=" << gate_context._conn_seq_id;
	
		// 删除连接对应的session
		DelSession* ds = new DelSession(_proc, gate_context._conn_seq_id);
		ds->del_session();
	}
}

void GateServer::on_message(const muduo::net::TcpConnectionPtr& conn, 
							PacketPtr& packet_ptr,
							muduo::Timestamp time)
{
	GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
	if(p_gate_context->_is_client_init_conn_seq_id)
	{
		// 客户端获取到连接id
		if(packet_ptr->_to_service_id == Define::service_id)
		{
			// 处理client返回gate的rsp
			TaskMsgBase* task = _proc._task_msg_pool.find(packet_ptr->_msg_seq_id);
			if(task == nullptr)
			{
				B_LOG_ERROR << "no find msg_seq_id=" << packet_ptr->_msg_seq_id;
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
				}
			}
		}
		else if(packet_ptr->_conn_seq_id == p_gate_context->_conn_seq_id)
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
		// 客户端没获取到连接id
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
				B_LOG_ERROR	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
							<< ", msg_type is rsp";
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
		}
	}

	p_gate_context->_update_time = ::time(nullptr);
}

void GateServer::on_write_complete(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name();

	/*
	GateServer发送给client时不用更新时间，避免与主动发送GateMsg::WakeHeartbeatReq的功能冲突，
	导致p_gate_context->_update_time一直更新，不能触发on_check_idle关闭连接

	GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
	p_gate_context->_update_time = ::time(nullptr);
	*/
}

void GateServer::on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len)
{
	LOG_WARN << conn->name() << ", len=" << len;

	GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
	p_gate_context->_update_time = ::time(nullptr);
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
			if(p_gate_context->_is_wake_heartbeat_wait)
			{
				// 等待客户端心跳返回，无需处理
			}
			else if(t_now - p_gate_context->_update_time >= _proc._config.proc.gate_server_idle)
			{
				// 给客户端发送心跳请求
				WakeHeartbeat* whb = new WakeHeartbeat(_proc, p_gate_context->_conn_seq_id);
				whb->wake_client(conn, p_gate_context);
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




