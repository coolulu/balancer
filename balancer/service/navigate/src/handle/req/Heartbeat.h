#pragma once

#include "Packet.h"
#include "BTcpServer.h"
#include "protocol/Protocol.h"

class Heartbeat
{
public:
	Heartbeat(BTcpServer& tcp_server, 
			  const muduo::net::TcpConnectionPtr& conn,
			  PacketPtr& packet_ptr,
			  muduo::Timestamp time);
	~Heartbeat();

public:
	void handle(const center::CenterMsg& msg);


private:
	BTcpServer& _tcp_server;
	const muduo::net::TcpConnectionPtr& _conn;
	PacketPtr _packet_ptr;
	muduo::Timestamp _time;

};