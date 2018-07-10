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
					 PacketPtr& packetPtr);

private:
	PacketMessageCallback _messageCallback;	
	const std::string _name;
	unsigned int& _tcp_recv_packet_len_max;
	unsigned int& _tcp_send_packet_len_max;
};


