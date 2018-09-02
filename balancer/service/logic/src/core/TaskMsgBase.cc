#include "TaskMsgBase.h"

#include "core/Proc.h"

TaskMsgBase::TaskMsgBase(Proc& proc, 
						 const std::string& task_name, 
						 unsigned int gap_us)
	:	_proc(proc),
		_task_name(task_name),
		_seq_id(proc._seq.make_seq()),
		_gap_us(gap_us),
		_is_timeout(false),
		_begin_time_us(0),
		_end_time_us(0),
		_delay_us(0),
		_state(0),
		_code(0)
{

}

TaskMsgBase::~TaskMsgBase()
{

}

bool TaskMsgBase::check_timeout(unsigned long long now_us)
{
	unsigned long long delay_us = now_us - _begin_time_us;
	if(delay_us < _gap_us)
	{
		return false;
	}

	_is_timeout = true;
	_end_time_us = now_us;
	_delay_us = delay_us;

	return true;
}

void TaskMsgBase::print(const std::string& prefix)
{
	B_LOG_INFO	<< "prefix=" << prefix
				<< ", _task_name=" << _task_name 
				<< ", _seq_id=" << _seq_id 
				<< ", _gap_us=" << _gap_us
				<< ", _is_timeout=" << _is_timeout 
				<< ", _begin_time_us=" << _begin_time_us
				<< ", _end_time_us=" << _end_time_us 
				<< ", _delay_us=" << _delay_us
				<< ", _state=" << _state
				<< ", _code=" << _code
				<< ", _info=" << _info;
}

TaskMsgMaster::TaskMsgMaster(Proc& proc, const std::string& task_name, unsigned int gap_us)
	:	TaskMsgBase(proc, task_name, gap_us)
{

}

TaskMsgMaster::~TaskMsgMaster()
{
	for(auto it = _sub_set.begin(); it != _sub_set.end(); it++)
	{
		_proc._task_msg_pool.del(*it);
	}
}

TaskMsgSub::TaskMsgSub(Proc& proc, const std::string& task_name, unsigned int gap_us,
					   TaskMsgMaster* p_task_msg_master)
	:	TaskMsgBase(proc, task_name, gap_us),
		_p_task_msg_master(p_task_msg_master)
{

}

TaskMsgSub::~TaskMsgSub()
{
	_p_task_msg_master = nullptr; // ²»ÓÃÊÍ·Å
}

int TaskMsgSub::timeout()
{

}

int TaskMsgSub::run(void* p)
{

}


