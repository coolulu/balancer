#pragma once

#include "core/TaskMsgBase.h"
#include "config/ServiceConfig.h"

class Proc;

class SyncServiceReq : public TaskMsgBase
{
public:
	SyncServiceReq(Proc& proc);
	~SyncServiceReq();

public:
	static const std::string& s_task_name;

public:
	void sync();
	virtual int timeout();
	virtual int run(void* p = nullptr);

private:
	ServiceConfig::IPInfo _ip_info;


};