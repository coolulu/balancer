#pragma once

#include "core/Packet.h"
#include "core/Proc.h"
#include "protocol/Protocol.h"

class SyncServiceRsp
{
public:
	SyncServiceRsp(Proc& proc, 
				   const muduo::net::TcpConnectionPtr& conn,
				   PacketPtr& packet_ptr,
				   muduo::Timestamp time);
	~SyncServiceRsp();

public:
	void handle(const center::CenterMsg& msg);

private:
	Proc& _proc;
	const muduo::net::TcpConnectionPtr& _conn;
	PacketPtr _packet_ptr;
	muduo::Timestamp _time;

};