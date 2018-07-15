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

void BTcpClient::send_msg(PacketPtr& msg)
{
	if(_connect)
	{	
		muduo::net::TcpConnectionPtr tcpConnectionPtr = _tcp_client.connection();
		if(tcpConnectionPtr)
		{
			_codec.send_stream(get_pointer(tcpConnectionPtr), msg);
		}
		else
		{
			_connect = false;

			_msg_send_buffer.push_back(msg);
			B_LOG_WARN << "save msg, _msg_seq_id=" << msg->_msg_seq_id << ", _msg_send_buffer.size=" << _msg_send_buffer.size();
			check_send_buffer_reduce();
		}
	}
	else
	{
		_msg_send_buffer.push_back(msg);
		B_LOG_INFO << "connecting, _msg_seq_id=" << msg->_msg_seq_id << ", _msg_send_buffer.size=" << _msg_send_buffer.size();
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
				_codec.send_stream(get_pointer(conn), msg);
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
	
#include "protocol/protobuf/proto_cpp/center.pb.h"
void BTcpClient::on_message(const muduo::net::TcpConnectionPtr& conn, 
							PacketPtr& packet_ptr, 
							muduo::Timestamp time)
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
			const ::data::Body_MsgRsq& msg_rsp = packet_ptr->_body.msg_rsp();

			B_LOG_INFO	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString()
						<< ", msg_type is rsp" << ", code=" << msg_rsp.code() << ", info=" << msg_rsp.info();

			const ::google::protobuf::Any& service_msg = packet_ptr->_body.service_msg();
			if(service_msg.Is<center::CenterMsg>())
			{
				B_LOG_INFO << "center::CenterMsg";
				center::CenterMsg msg;
				service_msg.UnpackTo(&msg);

				switch(msg.choice_case())
				{
				case center::CenterMsg::kHeartbeatRsp:
					{
						B_LOG_INFO << "center::HeartbeatRsp";
						const center::HeartbeatRsp& rsp = msg.heartbeat_rsp();
						B_LOG_INFO << "level=" << rsp.level();
						B_LOG_INFO << "service_id=" << rsp.service_id();
						B_LOG_INFO << "proc_id=" << rsp.proc_id();
						B_LOG_INFO << "conf_update_time=" << rsp.conf_update_time();
						B_LOG_INFO << "role_expire_time=" << rsp.role_expire_time();
					}
					break;
				}
			}
		}
		break;

	default:
		B_LOG_ERROR	<< conn->name() << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", _len=" << packet_ptr->_len << ", time=" << time.toString() 
					<< ", unknow msg_type=" << msg_type;
		break;
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
	LOG_WARN << conn->name() << ", len=" << len;

	_update_time = ::time(nullptr);
}

void BTcpClient::check_send_buffer_reduce()
{
	if(_msg_send_buffer.size() >= _proc._config.proc.tcp_client_msg_reduce_size)
	{
		std::vector<PacketPtr> msg_send_buffer(_msg_send_buffer.begin() + _msg_send_buffer.size() / 2, 
											   _msg_send_buffer.end());
		for(unsigned int i = 0; i != _msg_send_buffer.size() / 2; i++)
		{
			B_LOG_WARN << "discard msg, _msg_seq_id=" << _msg_send_buffer[i]->_msg_seq_id;
		}

		_msg_send_buffer.swap(msg_send_buffer);
		B_LOG_WARN << "reduce _msg_send_buffer.size=" << _msg_send_buffer.size();
	}
}





