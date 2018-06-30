#pragma once

namespace SignalHandle
{
	void init_signal();
	void set_reload_flag(int sig);
	void set_stop_flag(int sig);
};
