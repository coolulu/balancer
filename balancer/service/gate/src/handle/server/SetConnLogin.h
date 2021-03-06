#pragma once

#include "core/Packet.h"
#include "core/Proc.h"
#include "protocol/Protocol.h"

class SetConnLogin
{
public:
	SetConnLogin(Proc& proc, 
				 const muduo::net::TcpConnectionPtr& conn,
				 PacketPtr& packet_ptr,
				 muduo::Timestamp time);
	~SetConnLogin();

public:
	void handle(const gate::GateMsg& msg);

private:
	Proc& _proc;
	const muduo::net::TcpConnectionPtr& _conn;
	PacketPtr _packet_ptr;
	muduo::Timestamp _time;
};