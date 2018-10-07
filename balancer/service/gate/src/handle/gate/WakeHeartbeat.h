#pragma once

#include "muduo/net/TcpConnection.h"
#include "core/TaskMsgBase.h"

class GateContext;

class WakeHeartbeat : public TaskMsgBase
{
public:
	WakeHeartbeat(Proc& proc, unsigned long long conn_seq_id);
	virtual ~WakeHeartbeat();

public:
	virtual int timeout();
	virtual int run(void* p = nullptr);
	void wake_client(muduo::net::TcpConnectionPtr& conn, GateContext* p_gate_context);

public:
	static const std::string& s_task_name;

private:
	unsigned long long _conn_seq_id;
	unsigned long long _server_time;

};