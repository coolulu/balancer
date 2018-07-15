#include "SignalHandle.h"

#include <signal.h>
#include "Proc.h"

void SignalHandle::init_signal()
{
	::signal(SIGPIPE, SIG_IGN);
	::signal(SIGUSR1, set_reload_flag);
	::signal(SIGUSR2, set_stop_flag);
}

void SignalHandle::set_reload_flag(int sig)
{
	Proc::set_reload(true);
}

void SignalHandle::set_stop_flag(int sig)
{
	Proc::set_stop(true);
}
