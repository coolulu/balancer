#include <unistd.h>
#include <muduo/net/EventLoop.h>
#include "Log.h"
#include "SignalHandle.h"
#include "Util.h"
#include "Proc.h"

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		B_LOG_ERROR << "bin/center -f conf/center_1.json -d";
		return -10;
	}

	char flag;
	std::string config_file;
	bool daemon = false;
	while((flag = getopt(argc, argv, "f:d::")) != -1)
	{
		switch (flag)
		{
		case 'f':
			config_file = optarg;	
			break;
		case 'd':
			daemon = true;
			break;
		}
	}	

	if(config_file.empty())
	{
		B_LOG_ERROR << "config_file is empty";
		return -20;
	}

	B_LOG_INFO << "config_file=" << config_file << ", daemon=" << (daemon ? "true" : "false");

	int ret = 0;
	std::string err;

	if(daemon)
	{
		ret = Util::daemon_run();
		if(ret != 0)
		{
			B_LOG_ERROR << "daemon is error";
			return -20;
		}
	}

	{	
		int cpu_size = sysconf(_SC_NPROCESSORS_CONF);
		unsigned short cpu_id = Util::get_cpu_id(config_file) % cpu_size;

		cpu_set_t cpu_mask;
		err = Util::get_cpu_mask(0, &cpu_mask);
		if(err.size() > 0)
		{
			B_LOG_ERROR << err;
			return -30;
		}
		B_LOG_INFO << Util::print_cpu_mask(cpu_mask);
	
		err = Util::set_cpu_mask(cpu_id, &cpu_mask);
		if(err.size() > 0)
		{
			B_LOG_ERROR << err;
			return -31;
		}

		err = Util::get_cpu_mask(0, &cpu_mask);
		if(err.size() > 0)
		{
			B_LOG_ERROR << err;
			return -32;
		}

		B_LOG_INFO << Util::print_cpu_mask(cpu_mask);
		B_LOG_INFO << "bind cpu_id " << cpu_id;
	}

	SignalHandle::init_signal();

	muduo::net::EventLoop loop;	//安全关闭，loop声明周期要长于proc
	Proc proc(loop, config_file);
	ret = proc.init();
	if(ret != 0)
	{
		B_LOG_ERROR << "proc init error, ret=" << ret;
		return ret;
	}

	proc.start();
	proc.loop();

	B_LOG_INFO << "stop end";

	return 0;
}