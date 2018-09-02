#pragma once

#include <vector>
#include <map>

#include "TaskMsgBase.h"

class TaskMsgPool
{
public:
	TaskMsgPool();
	~TaskMsgPool();

public:
	inline unsigned int index(unsigned long long seq_id){return seq_id % s_size;}

	TaskMsgBase* find(unsigned long long seq_id);
	void add(TaskMsgBase* task);
	void del(unsigned long long seq_id);

	void clear();
	unsigned int size();
	void check_timeout();

private:
	const static unsigned int s_size = 1000;

	std::vector<std::map<unsigned long long, TaskMsgBase*>> _map_v_task;
	std::vector<TaskMsgBase*> _vec_timeout_task;
};
