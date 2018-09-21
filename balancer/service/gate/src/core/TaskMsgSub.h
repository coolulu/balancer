#pragma once

#include "core/TaskMsgBase.h"
#include "config/ServiceConfig.h"

class TaskMsgMaster;

// 子任务
class TaskMsgSub : public TaskMsgBase
{
public:
	// gap_us等于0则不放入定时器，则不用等待rsp或timeout，必须是栈变量，否则内存泄露
	// gap_us不等于0则放入定时器，必须是指针，否则挂掉
	// proc_id等于0，则轮询
	// proc_id不等于0，则指定proc_id
	TaskMsgSub(Proc& proc,
			   const std::string& task_name,
			   unsigned int gap_us,
			   unsigned short depend_service_id,
			   unsigned int proc_id,
			   TaskMsgMaster* p_task_msg_master);
	virtual ~TaskMsgSub();

private:
	enum
	{
		EN_STATE_REQUEST	= 10,
		EN_STATE_RESPONSE	= 20,
	};

public:
	virtual int timeout();
	virtual int run(void* p = nullptr);
	virtual void print(const std::string& prefix = "");

public:
	unsigned short _depend_service_id;
	unsigned int _proc_id;
	ServiceConfig::IPInfo _ip_info;
	TaskMsgMaster* _p_task_msg_master;
	
};

