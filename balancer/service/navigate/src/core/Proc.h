#pragma once

#include <muduo/net/EventLoop.h>

#include "log/Log.h"
#include "config/Config.h"
#include "config/ServiceConfig.h"
#include "Timer.h"
#include "BTcpServer.h"
#include "BHttpServer.h"
#include "Seq.h"
#include "Owner.h"

class Proc
{
public:
	Proc(muduo::net::EventLoop& loop, 
		 const std::string& config_file,
		 unsigned int conf_id);
	~Proc();

public:
	int init();
	void start();
	void quit();
	void loop();

public:
	static inline void set_reload(bool b)	{Proc::s_reload_flag = b;}
	static inline void set_stop(bool b)		{Proc::s_stop_flag = b;}
	static inline bool reload()				{return Proc::s_reload_flag;}
	static inline bool stop()				{return Proc::s_stop_flag;}

private:
	static bool s_reload_flag;
	static bool s_stop_flag;

public:
	const std::string _config_file;
	const unsigned int _conf_id;

	Seq _seq;
	Log _log;
	Config _config;
	ServiceConfig _sc;
	
	BTcpServer _tcp_server;
	BHttpServer _http_server;
	Timer _timer;

	Owner _owner;

	muduo::net::EventLoop& _loop;
};