#pragma once

#include <muduo/net/TcpConnection.h>
#include "core/Packet.h"
#include "core/TaskMsgPool.h"

class Proc;

class HandleGate
{
public:
	HandleGate(Proc& proc);
	~HandleGate();

public:
	void handle_request(const muduo::net::TcpConnectionPtr& conn, 
						PacketPtr& packet_ptr,
						muduo::Timestamp time);

	void handle_response(const muduo::net::TcpConnectionPtr& conn, 
						 TaskMsgBase* task,
						 muduo::Timestamp time);

	void forward_request_to_service(const muduo::net::TcpConnectionPtr& conn,
									PacketPtr& packet_ptr,
									muduo::Timestamp time);

	void forward_response_to_service(const muduo::net::TcpConnectionPtr& conn,
									 PacketPtr& packet_ptr,
									 muduo::Timestamp time);

private:
	Proc& _proc;

};
