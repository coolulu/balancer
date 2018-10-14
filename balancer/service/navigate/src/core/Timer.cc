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
	_proc._count_load.check_count();
}