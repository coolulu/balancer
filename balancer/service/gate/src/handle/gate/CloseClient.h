#pragma once

#include "muduo/net/TcpConnection.h"
#include "core/TaskMsgBase.h"

class CloseClient : public TaskMsgBase
{
public:
	CloseClient(Proc& proc, 
				PacketPtr& packet_ptr_req,
				unsigned long long _client_conn_id,
				unsigned long long _rsp_conn_id);
	virtual ~CloseClient();

public:
	virtual int timeout();
	virtual int run(void* p = nullptr);
	void close_client(muduo::net::TcpConnectionPtr& conn);
	void handle(bool is_timeout);

public:
	static const std::string& s_task_name;

private:
	PacketPtr _packet_ptr_req;
	unsigned long long _client_conn_id;
	unsigned long long _rsp_conn_id;
	
};