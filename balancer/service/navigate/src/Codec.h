#pragma once

#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include "Packet.h"

class Codec : boost::noncopyable
{
public:
	typedef boost::function<void (const muduo::net::TcpConnectionPtr&,
								  Packet& packet,
								  muduo::Timestamp)> PacketMessageCallback;

	explicit Codec(const PacketMessageCallback& cb,
				   const std::string& name,
			       unsigned int& tcp_recv_packet_len_max, 
				   unsigned int& tcp_send_packet_len_max);
public:
	void on_stream_message(const muduo::net::TcpConnectionPtr& conn,
						   muduo::net::Buffer* buf,
						   muduo::Timestamp receiveTime);

	void send_stream(muduo::net::TcpConnection* conn,
					 unsigned short version,  
					 unsigned short from_service_id,
					 unsigned short to_service_id,
					 unsigned int to_proc_id,
					 unsigned int app_id,
					 unsigned int app_version,
					 unsigned long long conn_seq_id,
					 unsigned long long msg_seq_id,
					 unsigned char data_format,
					 unsigned char* data,
					 unsigned int data_len,
					 unsigned char reserve_field_0 = 0,
					 unsigned int reserve_field_1 = 0,
					 unsigned int reserve_field_2 = 0,
					 unsigned int reserve_field_3 = 0);

private:
	PacketMessageCallback _messageCallback;	
	const std::string _name;
	unsigned int& _tcp_recv_packet_len_max;
	unsigned int& _tcp_send_packet_len_max;
};


