#include "Timer.h"
#include "log/Log.h"
#include "Proc.h"
#include "tool/Util.h"

Timer::Timer(Proc& proc) : _proc(proc)
{

}

Timer::~Timer()
{

}

void Timer::check_timeout()
{
	unsigned long long now_us = Util::get_us();	

	_proc.check_flag();
}