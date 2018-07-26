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
	_proc._prober.probe(now_us);
	_proc._tcp_client_pool.check_idle(now_us);
		
}