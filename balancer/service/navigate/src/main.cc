#include <unistd.h>
#include <muduo/net/EventLoop.h>
#include "log/Log.h"
#include "core/SignalHandle.h"
#include "tool/Util.h"
#include "core/Proc.h"

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		B_LOG_ERROR << "bin/navigate -f conf/navigate_0.json -d";
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

	unsigned int conf_id = Util::get_conf_id(config_file);

	SignalHandle::init_signal();

	muduo::net::EventLoop loop;	//安全关闭，loop声明周期要长于proc
	Proc proc(loop, config_file, conf_id);
	ret = proc.init();
	if(ret != 0)
	{
		B_LOG_ERROR << "proc init error, ret=" << ret;
		return ret;
	}

	proc.logging();
	proc.start();
	proc.loop();

	B_LOG_ERROR << "stop end";

	return 0;
}