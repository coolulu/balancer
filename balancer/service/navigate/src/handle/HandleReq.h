#pragma once

#include <muduo/net/TcpConnection.h>
#include "Packet.h"

class BTcpServer;

class HandleReq
{
public:
	HandleReq(BTcpServer& tcp_server);
	~HandleReq();

public:
	void handle(const muduo::net::TcpConnectionPtr& conn, 
				PacketPtr& packet_ptr,
				muduo::Timestamp time);


private:
	BTcpServer& _tcp_server;

};
