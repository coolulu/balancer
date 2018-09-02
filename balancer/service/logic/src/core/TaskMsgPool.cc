#include "TaskMsgPool.h"

#include "tool/Util.h"

TaskMsgPool::TaskMsgPool()
	:	_map_v_task(s_size)
{

}

TaskMsgPool::~TaskMsgPool()
{
	clear();
}

TaskMsgBase* TaskMsgPool::find(unsigned long long seq_id)
{
	unsigned int i = index(seq_id);
	std::map<unsigned long long, TaskMsgBase*>& m = _map_v_task[i];

	auto it = m.find(seq_id);
	return it != m.end() ? it->second : nullptr;
}

void TaskMsgPool::add(TaskMsgBase* task)
{
	unsigned int i = index(task->_seq_id);
	std::map<unsigned long long, TaskMsgBase*>& m = _map_v_task[i];

	m.insert(std::make_pair(task->_seq_id, task));
}

void TaskMsgPool::del(unsigned long long seq_id)
{
	unsigned int i = index(seq_id);
	std::map<unsigned long long, TaskMsgBase*>& m = _map_v_task[i];

	auto it = m.find(seq_id);
	if(it != m.end())
	{
		delete it->second;
		it->second = nullptr;
		m.erase(it);
	}
}

void TaskMsgPool::clear()
{
	for(auto i = 0; i != s_size; i++)
	{
		for(auto it = _map_v_task[i].begin(); it != _map_v_task[i].end(); it++)
		{
			delete it->second;
			it->second = nullptr;
		}

		_map_v_task[i].clear();
	}
}

unsigned int TaskMsgPool::size()
{
	unsigned int count = 0;
	for(auto i = 0; i != s_size; i++)
	{
		count += _map_v_task[i].size();
	}

	return count;
}

void TaskMsgPool::check_timeout()
{
	unsigned long long now_us = Util::get_us();	

	for(auto i = 0; i != s_size; i++)
	{
		std::map<unsigned long long, TaskMsgBase*>& m = _map_v_task[i];
		for(auto it = m.begin();  it != m.end(); it++)
		{
			bool b = it->second->check_timeout(now_us);
			if(b)
			{
				_vec_timeout_task.push_back(it->second);
			}
		}
	}

	if(_vec_timeout_task.size() > 0)
	{
		for(unsigned int i = 0; i != _vec_timeout_task.size(); i++)
		{
			TaskMsgBase* task = _vec_timeout_task[i];
			task->timeout();
			del(task->_seq_id);
			task = nullptr;
		}

		_vec_timeout_task.clear();
	}
}



