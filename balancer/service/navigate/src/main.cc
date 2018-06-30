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
		B_LOG_ERROR << "bin/navigate -f conf/navigate_1.json -d";
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

	SignalHandle::init_signal();

	muduo::net::EventLoop loop;	//��ȫ�رգ�loop��������Ҫ����proc
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