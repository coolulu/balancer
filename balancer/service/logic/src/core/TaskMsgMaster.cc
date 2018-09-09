#include "TaskMsgMaster.h"

#include "core/Proc.h"
#include "core/TaskMsgSub.h"

TaskMsgMaster::TaskMsgMaster(Proc& proc, const std::string& task_name, unsigned int gap_us)
	:	TaskMsgBase(proc, task_name, gap_us)
{

}

TaskMsgMaster::~TaskMsgMaster()
{
	sub_clear();
}

unsigned int TaskMsgMaster::sub_size()
{
	return _sub_set.size();
}

bool TaskMsgMaster::sub_is_empty()
{
	return _sub_set.empty();
}

void TaskMsgMaster::sub_clear()
{
	for(auto it = _sub_set.begin(); it != _sub_set.end(); it++)
	{
		_proc._task_msg_pool.del(*it);
	}
}

void TaskMsgMaster::sub_insert(unsigned int sub_seq_id)
{
	_sub_set.insert(sub_seq_id);
}

bool TaskMsgMaster::sub_remove(unsigned int sub_seq_id)
{
	auto count = _sub_set.erase(sub_seq_id);
	return count != 0;
}

