#pragma once

#include "core/TaskMsgBase.h"
#include "config/ServiceConfig.h"

class TaskMsgMaster;

// всхннЯ
class TaskMsgSub : public TaskMsgBase
{
public:
	TaskMsgSub(Proc& proc, 
			   const std::string& task_name, 
			   unsigned int gap_us,
			   TaskMsgMaster* p_task_msg_master);
	virtual ~TaskMsgSub();

public:
	virtual int timeout();
	virtual int run(void* p = nullptr);
	virtual void print(const std::string& prefix = "");

public:
	TaskMsgMaster* _p_task_msg_master;
	ServiceConfig::IPInfo _ip_info;
};

