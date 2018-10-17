#include "Timer.h"
#include "log/Log.h"
#include "Proc.h"

Timer::Timer(Proc& proc) : _proc(proc)
{

}

Timer::~Timer()
{

}

void Timer::check_timeout()
{
	_proc.check_flag();
	_proc._prober.probe();
	_proc._tcp_client_pool.check_idle();
	_proc._task_msg_pool.check_timeout();	
	_proc._synchro.check_sync();
}