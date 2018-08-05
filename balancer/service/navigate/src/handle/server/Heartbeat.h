#pragma once

#include "core/Packet.h"
#include "core/Proc.h"
#include "protocol/Protocol.h"

class Heartbeat
{
public:
	Heartbeat(Proc& proc, 
				 const muduo::net::TcpConnectionPtr& conn,
				 PacketPtr& packet_ptr,
				 muduo::Timestamp time);
	~Heartbeat();

public:
	void handle(const center::CenterMsg& msg);

private:
	void save_conf(const center::HeartbeatReq& req);

private:
	Proc& _proc;
	const muduo::net::TcpConnectionPtr& _conn;
	PacketPtr _packet_ptr;
	muduo::Timestamp _time;

};