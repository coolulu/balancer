#include "BTcpServer.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "Log.h"

Context::Context(unsigned int seq_id)
	: _seq_id(seq_id), _create_time(0), _update_time(0)
{
	_create_time = time(nullptr);
	_update_time = _create_time;
}

BTcpServer::BTcpServer(Proc& proc)
	: _proc(proc), _p_tcp_server(nullptr),
	  _codec(boost::bind(&BTcpServer::on_message, this, _1, _2, _3), "TcpServer",
			proc._config.proc.tcp_client_recv_packet_len_max,
			proc._config.proc.tcp_client_send_packet_len_max)
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
							Packet& packet,
							muduo::Timestamp time)
{
	std::string str((char*)packet._data, packet._data_len);
	B_LOG_INFO	<< conn->name() << " " 
				<< packet._len << " bytes, " << "data received at " << time.toString() 
				<< " msg: " << str;
	_codec.send_stream(get_pointer(conn), 110, 120, 130, 140, 150, 160, 170, 180, 190,
		packet._data, packet._data_len);

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


