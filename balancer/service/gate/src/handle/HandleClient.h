#pragma once

#include <muduo/net/TcpConnection.h>
#include "core/Packet.h"
#include "core/TaskMsgPool.h"

class Proc;

class HandleClient
{
public:
	HandleClient(Proc& proc);
	~HandleClient();

public:
	void handle_response(const muduo::net::TcpConnectionPtr& conn, 
						 TaskMsgBase* task,
						 muduo::Timestamp time);

	void forward_response_to_client(const muduo::net::TcpConnectionPtr& conn, 
									PacketPtr& packet_ptr,
									muduo::Timestamp time);

private:
	Proc& _proc;

};
