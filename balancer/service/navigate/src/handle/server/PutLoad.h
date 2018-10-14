#pragma once

#include "core/Packet.h"
#include "core/Proc.h"
#include "protocol/Protocol.h"

class PutLoad
{
public:
	PutLoad(Proc& proc, 
			const muduo::net::TcpConnectionPtr& conn,
			PacketPtr& packet_ptr,
			muduo::Timestamp time);
	~PutLoad();

public:
	// 只接受req，不需要返回rsp
	void handle(const navigate::NavigateMsg& msg);

private:
	Proc& _proc;
	const muduo::net::TcpConnectionPtr& _conn;
	PacketPtr _packet_ptr;
	muduo::Timestamp _time;

};