#pragma once

#include <muduo/net/TcpConnection.h>
#include "core/Packet.h"

class Proc;

class HandleServer
{
public:
	HandleServer(Proc& proc);
	~HandleServer();

public:
	void handle(const muduo::net::TcpConnectionPtr& conn, 
				PacketPtr& packet_ptr,
				muduo::Timestamp time);


private:
	Proc& _proc;

};
