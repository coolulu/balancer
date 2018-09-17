#include "BTcpServer.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "log/Log.h"

Context::Context(unsigned int seq_id)
	: _seq_id(seq_id), _create_time(0), _update_time(0)
{
	_create_time = time(nullptr);
	_update_time = _create_time;
}

BTcpServer::BTcpServer(Proc& proc)
	:	_proc(proc), _p_tcp_server(nullptr),
		_codec(	boost::bind(&BTcpServer::on_message, this, _1, _2, _3), "TcpServer",
				proc._config.proc.tcp_server_recv_packet_len_max,
				proc._config.proc.tcp_server_send_packet_len_max),
		_handle_server(proc)
{
	
}

BTcpServer::~BTcpServer()
{
	if(_p_tcp_server == nullptr)
	{
		delete _p_tcp_server;
		_p_tcp_server = nullptr;
	}
}

void BTcpServer::start()
{
	if(_p_tcp_server == nullptr)
	{
		_p_tcp_server = new muduo::net::TcpServer(&_proc._loop, 
			muduo::net::InetAddress(_proc._config.net.tcp.ip, _proc._config.net.tcp.port), "TcpServer");
		_p_tcp_server->setConnectionCallback(
			boost::bind(&BTcpServer::on_connection, this, _1));
		_p_tcp_server->setMessageCallback(
			boost::bind(&Codec::on_stream_message, &_codec, _1, _2, _3));
		_p_tcp_server->setWriteCompleteCallback(
			boost::bind(&BTcpServer::on_write_complete, this, _1));
		_p_tcp_server->start();

		_proc._loop.runEvery(1.0, boost::bind(&BTcpServer::on_check_idle, this));
	}
}

bool BTcpServer::send_msg(const muduo::net::TcpConnectionPtr& conn, PacketPtr& msg)
{
	if(conn)
	{
		_codec.send_stream(get_pointer(conn), msg);
		return true;
	}

	B_LOG_WARN << "conn is null, msg is lose, _msg_seq_id=" << msg->_msg_seq_id;
	return false;
}

void BTcpServer::on_connection(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name() << " " 
				<< conn->peerAddress().toIpPort() << " -> " 
				<< conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");
	
	if(conn->connected())
	{
		conn->setTcpNoDelay(_proc._config.proc.tcp_server_no_delay);
		conn->setHighWaterMarkCallback(boost::bind(&BTcpServer::on_high_water_mark, this, _1, _2),
			_proc._config.proc.tcp_server_high_water_mark);

		Context context(_proc._seq.make_seq());
		conn->setContext(context);
		_conn_map.insert(std::make_pair(context._seq_id, conn));
	}
	else
	{
		const Context& context = boost::any_cast<const Context&>(conn->getContext());
		_conn_map.erase(context._seq_id);
	}
}

void BTcpServer::on_message(const muduo::net::TcpConnectionPtr& conn, 
							PacketPtr& packet_ptr,
							muduo::Timestamp time)
{
	int msg_type = packet_ptr->_body.msg_type_case();
	switch(msg_type)
	{
	case data::Body::kMsgReq:
		{
			const ::data::Body_MsgReq& msg_req = packet_ptr->_body.msg_req();

			B_LOG_INFO	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
						<< ", msg_type is req";

			_handle_server.handle_request(conn, packet_ptr, time);
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

	Context* p_context = boost::any_cast<Context>(conn->getMutableContext());
	p_context->_update_time = ::time(nullptr);
}

void BTcpServer::on_write_complete(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name();

	Context* p_context = boost::any_cast<Context>(conn->getMutableContext());
	p_context->_update_time = ::time(nullptr);
}

void BTcpServer::on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len)
{
	LOG_WARN << conn->name() << ", len=" << len;

	Context* p_context = boost::any_cast<Context>(conn->getMutableContext());
	p_context->_update_time = ::time(nullptr);
}

void BTcpServer::on_check_idle()
{
	unsigned int t_now = ::time(nullptr);
	for(auto it = _conn_map.begin(); it != _conn_map.end();)
	{
		muduo::net::TcpConnectionPtr conn = it->second;
		if(conn)
		{
			const Context& context = boost::any_cast<const Context&>(conn->getContext());
			if(t_now - context._update_time >= _proc._config.proc.tcp_server_idle)
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




