#include "Timer.h"
#include "Log.h"
#include "Proc.h"

Timer::Timer(Proc& proc) : _proc(proc)
{

}

Timer::~Timer()
{

}

void Timer::check_timeout()
{
	if(_proc.reload())
	{
		_proc.set_reload(false);
		B_LOG_INFO << "reload start";

		

		B_LOG_INFO << "reload end";
	}

	if(_proc.stop())
	{
		_proc.set_stop(false);
		B_LOG_INFO << "stop start";
		_proc.quit();
	}

//	B_LOG_INFO << "seq=" << _proc._seq.make_seq();

}