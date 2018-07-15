#pragma once

#include <muduo/net/TcpConnection.h>
#include "Packet.h"

class Proc;

class HandleReq
{
public:
	HandleReq(Proc& proc);
	~HandleReq();

public:
	void handle(const muduo::net::TcpConnectionPtr& conn, 
				PacketPtr& packet_ptr,
				muduo::Timestamp time);


private:
	Proc& _proc;

};
