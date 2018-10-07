#pragma once

#include "core/Packet.h"
#include "core/Proc.h"
#include "protocol/Protocol.h"

class CloseConnId
{
public:
	CloseConnId(Proc& proc, 
				const muduo::net::TcpConnectionPtr& conn,
				PacketPtr& packet_ptr,
				muduo::Timestamp time);
	~CloseConnId();

public:
	void handle(const gate::GateMsg& msg);

private:
	Proc& _proc;
};