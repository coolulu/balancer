#pragma once

#include <muduo/net/TcpConnection.h>
#include "core/Packet.h"

class Proc;

class HandleClient
{
public:
	HandleClient(Proc& proc);
	~HandleClient();

public:
	void forward_response_to_client(const muduo::net::TcpConnectionPtr& conn, 
									PacketPtr& packet_ptr,
									muduo::Timestamp time);

private:
	Proc& _proc;

};
