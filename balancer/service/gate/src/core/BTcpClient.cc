#include "BTcpClient.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "define.h"

int BTcpClient::s_count = 0;

BTcpClient::BTcpClient(Proc& proc, const ServiceConfig::IPInfo& ip_info)
	:	_proc(proc), 
		_create_time(0),
		_update_time(0),
		_connect(false), 
		_ip_info(ip_info), 
		_tcp_client(&proc._loop, 
					muduo::net::InetAddress(ip_info.in_ip, ip_info.in_port), 
					ip_info.proc_des.c_str()),
		_codec(boost::bind(&BTcpClient::on_message, this, _1, _2, _3), ip_info.proc_des,
			   proc._config.proc.tcp_client_recv_packet_len_max,
			   proc._config.proc.tcp_client_send_packet_len_max),
		_handle_client(proc)
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
	B_LOG_INFO << "proc_id=" << _ip_info.proc_id << ", in_ip=" << _ip_info.in_ip << ", in_port=" << _ip_info.in_port;
	_tcp_client.connect();

	_update_time = ::time(nullptr);
} 

bool BTcpClient::send_msg(PacketPtr& msg)
{
	bool b = false;
	if(_connect)
	{	
		muduo::net::TcpConnectionPtr tcpConnectionPtr = _tcp_client.connection();
		if(tcpConnectionPtr)
		{
			_codec.send_stream(get_pointer(tcpConnectionPtr), msg);
			b = true;
		}
		else
		{
			_connect = false;

			_msg_send_buffer.insert(std::make_pair(msg->_msg_seq_id, msg));
			B_LOG_WARN << "save msg, _msg_seq_id=" << msg->_msg_seq_id << ", _msg_send_buffer.size=" << _msg_send_buffer.size();
			check_msg_send_buffer_reduce();
		}
	}
	else
	{
		_msg_send_buffer.insert(std::make_pair(msg->_msg_seq_id, msg));
		B_LOG_INFO << "connecting, _msg_seq_id=" << msg->_msg_seq_id << ", _msg_send_buffer.size=" << _msg_send_buffer.size();
		check_msg_send_buffer_reduce();
	}

	_update_time = ::time(nullptr);
	return b;
}

bool BTcpClient::send_stream(PacketPtr& msg)
{
	if(msg->_buffer == nullptr ||  msg->_buffer_len == 0)
	{
		B_LOG_WARN	<< "_buffer=nullptr or _buffer_len=0, msg is lose, _msg_seq_id=" << msg->_msg_seq_id
					<< ", _buffer=" << msg->_buffer
					<< ", _buffer_len=" << msg->_buffer_len;
		return false;
	}

	bool b = false;
	if(_connect)
	{	
		muduo::net::TcpConnectionPtr tcpConnectionPtr = _tcp_client.connection();
		if(tcpConnectionPtr)
		{
			tcpConnectionPtr->send(msg->_buffer, msg->_buffer_len);
			b = true;
		}
		else
		{
			_connect = false;

			PacketStreamPtr stream(new PacketStream(msg));
			_stream_send_buffer.insert(std::make_pair(stream->_packet_ptr->_msg_seq_id, stream));
			B_LOG_WARN << "save msg, _msg_seq_id=" << stream->_packet_ptr->_msg_seq_id << ", _stream_send_buffer.size=" << _stream_send_buffer.size();
			check_stream_send_buffer_reduce();
		}
	}
	else
	{
		PacketStreamPtr stream(new PacketStream(msg));
		_stream_send_buffer.insert(std::make_pair(stream->_packet_ptr->_msg_seq_id, stream));
		B_LOG_INFO << "connecting, _msg_seq_id=" << stream->_packet_ptr->_msg_seq_id << ", _stream_send_buffer.size=" << _stream_send_buffer.size();
		check_stream_send_buffer_reduce();
	}

	_update_time = ::time(nullptr);
	return b;
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
			for(auto& it : _msg_send_buffer)
			{
				_codec.send_stream(get_pointer(conn), it.second);
			}
			_msg_send_buffer.clear();
		}

		if(_stream_send_buffer.empty())
		{
			B_LOG_INFO << "_stream_send_buffer is empty";
		}
		else
		{
			B_LOG_INFO << "_stream_send_buffer.size=" << _stream_send_buffer.size();
			for(auto& it : _stream_send_buffer)
			{
				conn->send(it.second->_buffer, it.second->_buffer_len);
			}
			_stream_send_buffer.clear();
		}

		_update_time = ::time(nullptr);
	}
	else
	{
		//触发主动关闭会导致对象已经析构，但依然会回调这个成员函数，所以else下面的代码不能有成员变量
	}
}

void BTcpClient::on_message(const muduo::net::TcpConnectionPtr& conn, 
							PacketPtr& packet_ptr, 
							muduo::Timestamp time)
{
	if(packet_ptr->_to_service_id == Define::service_id)
	{
		// 处理service返回gate的rsp
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
						_handle_client.handle_response(conn, task, time);
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
	else
	{
		// 转发响应给client
		_handle_client.forward_response_to_client(conn, packet_ptr, time);
	}

	_update_time = ::time(nullptr);
}

void BTcpClient::on_write_complete(const muduo::net::TcpConnectionPtr& conn)
{
	B_LOG_INFO	<< conn->name();

	_update_time = ::time(nullptr);
}

void BTcpClient::on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len)
{
	B_LOG_WARN << conn->name() << ", len=" << len;

	_update_time = ::time(nullptr);
}

void BTcpClient::check_msg_send_buffer_reduce()
{
	if(_msg_send_buffer.size() >= _proc._config.proc.tcp_client_msg_reduce_size)
	{
		int count = 0;
		int reduce_size = _proc._config.proc.tcp_client_msg_reduce_size / 2;

		for(auto it = _msg_send_buffer.begin(); it != _msg_send_buffer.end();)
		{
			if(++count <= reduce_size)
			{
				B_LOG_WARN << "discard msg, _msg_seq_id=" << it->second->_msg_seq_id;
				_msg_send_buffer.erase(it++);
			}
			else
			{
				break;
			}
		}

		B_LOG_WARN << "reduce _msg_send_buffer.size=" << _msg_send_buffer.size();
	}
}

void BTcpClient::check_stream_send_buffer_reduce()
{
	if(_stream_send_buffer.size() >= _proc._config.proc.tcp_client_msg_reduce_size)
	{
		int count = 0;
		int reduce_size = _proc._config.proc.tcp_client_msg_reduce_size / 2;

		for(auto it = _stream_send_buffer.begin(); it != _stream_send_buffer.end();)
		{
			if(++count <= reduce_size)
			{
				B_LOG_WARN << "discard msg, _msg_seq_id=" << it->second->_packet_ptr->_msg_seq_id;
				_stream_send_buffer.erase(it++);
			}
			else
			{
				break;
			}
		}

		B_LOG_WARN << "reduce _stream_send_buffer.size=" << _stream_send_buffer.size();
	}
}

bool BTcpClient::reomve_msg_send_buffer(unsigned long long msg_seq_id)
{
	auto i = _msg_send_buffer.erase(msg_seq_id);	// i = 0 or 1
	return i != 0;	// 返回true, 说明一定没发出去
}





