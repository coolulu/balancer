#pragma once

#include <muduo/net/TcpConnection.h>
#include "core/TaskMsgPool.h"

class Proc;

class HandleClient
{
public:
	HandleClient(Proc& proc);
	~HandleClient();

public:
	void handle(const muduo::net::TcpConnectionPtr& conn, 
				TaskMsgBase* task,
				muduo::Timestamp time);


private:
	Proc& _proc;

};
