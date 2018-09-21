#pragma once

#include "core/TaskMsgBase.h"
#include "config/ServiceConfig.h"

class TaskMsgMaster;

// ������
class TaskMsgSub : public TaskMsgBase
{
public:
	// gap_us����0�򲻷��붨ʱ�������õȴ�rsp��timeout��������ջ�����������ڴ�й¶
	// gap_us������0����붨ʱ����������ָ�룬����ҵ�
	// proc_id����0������ѯ
	// proc_id������0����ָ��proc_id
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

