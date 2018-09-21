#pragma once

#include "core/TaskMsgBase.h"

class TaskMsgSub;

// ������
class TaskMsgMaster : public TaskMsgBase
{
public:
	TaskMsgMaster(Proc& proc, 
				  const std::string& task_name, 
				  unsigned int gap_us);
	virtual ~TaskMsgMaster();

public:
	virtual int timeout_by_sub(TaskMsgSub& sub) = 0;
	virtual int timeout() = 0;
	virtual int run(void* p = nullptr) = 0;
	virtual void print(const std::string& prefix = "");

public:
	unsigned int sub_size();
	bool sub_is_empty();
	void sub_clear();
	void sub_insert(unsigned int sub_seq_id);
	bool sub_remove(unsigned int sub_seq_id);
	
public:
	enum EN_STATE
	{
		EN_STATE_INIT			=  0,	// �����ʼ��
		EN_STATE_SUCCESS		= -1,	// ������������
		EN_STATE_ERROR			= -2,	// ����������
		EN_STATE_TIMEOUT		= -3,	// ������ʱ����
		EN_STATE_TIMEOUT_BY_SUB	= -4,	// ������ʱ����
	};

public:
	std::set<unsigned long long> _sub_set;
};

