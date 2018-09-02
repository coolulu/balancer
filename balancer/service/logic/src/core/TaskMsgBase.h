#pragma once

#include <string>

#include "core/Packet.h"

class Proc;

class TaskMsgBase
{
public:
	TaskMsgBase(Proc& proc, 
				const std::string& task_name, 
				unsigned int gap_us);
	virtual ~TaskMsgBase();

public:
	bool check_timeout(unsigned long long now_us);
	virtual int timeout() = 0;
	virtual int run(void* p = nullptr) = 0;
	virtual void print(const std::string& prefix = "");

public:
	Proc& _proc;

	const std::string& _task_name;
	const unsigned long long _seq_id;
	unsigned int _gap_us;
	bool _is_timeout;
	unsigned long long _begin_time_us;
	unsigned long long _end_time_us;
	unsigned long long _delay_us;

	int _state;
	int _code;
	std::string _info;
	PacketPtr _request;
	PacketPtr _response;
};

// 主任务
class TaskMsgMaster : public TaskMsgBase
{
public:
	TaskMsgMaster(Proc& proc, 
				  const std::string& task_name, 
				  unsigned int gap_us);
	virtual ~TaskMsgMaster();

public:
	virtual int timeout() = 0;
	virtual int run(void* p = nullptr) = 0;
	virtual void print(const std::string& prefix = "");

public:
	std::set<unsigned long long> _sub_set;
};

// 子任务
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
};


