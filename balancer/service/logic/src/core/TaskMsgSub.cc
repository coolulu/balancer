#include "TaskMsgSub.h"

#include "core/Proc.h"
#include "core/TaskMsgMaster.h"

TaskMsgSub::TaskMsgSub(Proc& proc, const std::string& task_name, unsigned int gap_us,
					   TaskMsgMaster* p_task_msg_master)
	:	TaskMsgBase(proc, task_name, gap_us),
	   _p_task_msg_master(p_task_msg_master)
{

}

TaskMsgSub::~TaskMsgSub()
{
	_p_task_msg_master = nullptr; // ≤ª”√ Õ∑≈
}

int TaskMsgSub::timeout()
{

}

int TaskMsgSub::run(void* p)
{

}
