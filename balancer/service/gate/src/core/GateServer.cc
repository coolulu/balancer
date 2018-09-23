#include "GateServer.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "log/Log.h"

GateContext::GateContext(unsigned int seq_id)
	: _seq_id(seq_id), _create_time(0), _update_time(0), _get_conn_id(false)
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

void GateServer::on_connection(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name() << " " 
				<< conn->peerAddress().toIpPort() << " -> " 
				<< conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");
	B_LOG_INFO << conn->peerAddress().toIpPort() << " : " << conn->peerAddress().toIp();
	
	if(conn->connected())
	{
		conn->setTcpNoDelay(_proc._config.proc.gate_server_no_delay);
		conn->setHighWaterMarkCallback(boost::bind(&GateServer::on_high_water_mark, this, _1, _2),
			_proc._config.proc.gate_server_high_water_mark);

		GateContext gate_context(_proc._seq.make_seq());
		conn->setContext(gate_context);
		_conn_map.insert(std::make_pair(gate_context._seq_id, conn));
	}
	else
	{
		const GateContext& gate_context = boost::any_cast<const GateContext&>(conn->getContext());
		_conn_map.erase(gate_context._seq_id);
	}
}

void GateServer::on_message(const muduo::net::TcpConnectionPtr& conn, 
							PacketPtr& packet_ptr,
							muduo::Timestamp time)
{
	GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
	if(p_gate_context->_get_conn_id)
	{
		// 获取到连接id
		bool b = packet_ptr->parse();
		if(b)
		{
			int msg_type = packet_ptr->_body.msg_type_case();
			switch(msg_type)
			{
			case data::Body::kMsgReq:
				{
					const ::data::Body_MsgReq& msg_req = packet_ptr->_body.msg_req();

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
	else
	{
		// 没获取到连接id
		if(packet_ptr->_conn_seq_id == p_gate_context->_seq_id)
		{
			// 转发请求 s out -> c
		}
		else
		{
			// 转发响应 s out -> s in
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
			const GateContext& gate_context = boost::any_cast<const GateContext&>(conn->getContext());
			if(t_now - gate_context._update_time >= _proc._config.proc.gate_server_idle)
			{
				B_LOG_INFO << conn->name() << " is idle, shutdown";
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




