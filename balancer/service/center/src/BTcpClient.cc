#include "BTcpClient.h"

#include <boost/bind.hpp>
#include "Proc.h"

int BTcpClient::s_count = 0;

BTcpClient::BTcpClient(Proc& proc, const ServiceConfig::IPInfo& ip_info)
	:	_proc(proc), 
		_create_time(0),
		_update_time(0),
		_connect(false), 
		_ip_info(ip_info), 
		_tcp_client(&proc._loop, 
					muduo::net::InetAddress(ip_info.in_ip, ip_info.port), 
					ip_info.proc_des.c_str()),
		_codec(boost::bind(&BTcpClient::on_message, this, _1, _2, _3), ip_info.proc_des,
			   proc._config.proc.tcp_client_recv_packet_len_max,
			   proc._config.proc.tcp_client_send_packet_len_max)
{
	_create_time = ::time(nullptr);
	_update_time = _create_time;

	_tcp_client.setConnectionCallback(
		boost::bind(&BTcpClient::on_connection, this, _1));
	_tcp_client.setMessageCallback(
		boost::bind(&Codec::on_stream_message, &_codec, _1, _2, _3));
	_tcp_client.setWriteCompleteCallback(
		boost::bind(&BTcpClient::on_write_complete, this, _1));
	_tcp_client.enableRetry();	//开启自动重连

	B_LOG_INFO << _tcp_client.name() << ", s_count=" << ++s_count << ", _create_time=" << _create_time;
}

BTcpClient::~BTcpClient()
{
	B_LOG_INFO	<< _tcp_client.name()
				<< ", s_count=" << --s_count
				<< ", _create_time=" << _create_time 
				<< ", _update_time=" << _update_time 
				<< ", use= " << _update_time - _create_time;
}

bool BTcpClient::check_idle(unsigned int now)
{
	return now - _update_time >= _proc._config.proc.tcp_client_idle;
}

void BTcpClient::connect()
{
	B_LOG_INFO << "proc_id=" << _ip_info.proc_id << ", in_ip=" << _ip_info.in_ip << ", port=" << _ip_info.port;
	_tcp_client.connect();

	_update_time = ::time(nullptr);
} 

void BTcpClient::send_msg(const std::string& msg)
{
	if(_connect)
	{	
		muduo::net::TcpConnectionPtr tcpConnectionPtr = _tcp_client.connection();
		if(tcpConnectionPtr)
		{
			_codec.send_stream(get_pointer(tcpConnectionPtr), 10, 20, 30, 40, 50, 60, 70, 80, 90, 
				(unsigned char*)msg.c_str(), msg.size());
		}
		else
		{
			_connect = false;
		
			_msg_send_buffer.push_back(msg);
			B_LOG_WARN << "save msg, " << "msg.size=" << msg.size() << " _msg_send_buffer.size=" << _msg_send_buffer.size();
			check_send_buffer_reduce();
		}
	}
	else
	{
		_msg_send_buffer.push_back(msg);
		B_LOG_INFO << "_msg_send_buffer.size=" << _msg_send_buffer.size();
		check_send_buffer_reduce();
	}

	_update_time = ::time(nullptr);
}

void BTcpClient::on_connection(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name() << " " 
				<< conn->peerAddress().toIpPort() << " -> " 
				<< conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");

	if(conn->connected())
	{
		_connect = true;
		conn->setTcpNoDelay(_proc._config.proc.tcp_client_no_delay);
		conn->setHighWaterMarkCallback(boost::bind(&BTcpClient::on_high_water_mark, this, _1, _2), 
			_proc._config.proc.tcp_client_high_water_mark);

		if(_msg_send_buffer.empty())
		{
			B_LOG_INFO << "_msg_send_buffer is empty";
		}
		else
		{
			B_LOG_INFO << "_msg_send_buffer.size=" << _msg_send_buffer.size();
			for(auto& msg : _msg_send_buffer)
			{
				_codec.send_stream(get_pointer(conn), 10, 20, 30, 40, 50, 60, 70, 80, 90, 
					(unsigned char*)msg.c_str(), msg.size());
			}
			_msg_send_buffer.clear();
		}

		_update_time = ::time(nullptr);
	}
	else
	{
		//触发主动关闭会导致对象已经析构，但依然会回调这个成员函数，所以else下面的代码不能有成员变量
	}
}

void BTcpClient::on_message(const muduo::net::TcpConnectionPtr& conn, 
							Packet& packet, 
							muduo::Timestamp time)
{
	std::string str((char*)packet._data, packet._data_len);
	B_LOG_INFO	<< conn->name() << " " 
				<< packet._len << " bytes, " << "data received at " << time.toString() 
				<< " msg: " << str;

	_update_time = ::time(nullptr);
}

void BTcpClient::on_write_complete(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name();

	_update_time = ::time(nullptr);
}

void BTcpClient::on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len)
{
	LOG_WARN << conn->name() << ", len=" << len;

	_update_time = ::time(nullptr);
}

void BTcpClient::check_send_buffer_reduce()
{
	if(_msg_send_buffer.size() >= _proc._config.proc.tcp_client_msg_reduce_size)
	{
		std::vector<std::string> msg_send_buffer(_msg_send_buffer.begin() + _msg_send_buffer.size() / 2, 
												 _msg_send_buffer.end());
		_msg_send_buffer.swap(msg_send_buffer);
		B_LOG_WARN << "reduce _msg_send_buffer.size=" << _msg_send_buffer.size();
	}
}





