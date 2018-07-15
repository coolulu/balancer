#pragma once

#include <muduo/net/EventLoop.h>

#include "log/Log.h"
#include "config/Config.h"
#include "config/ServiceConfig.h"
#include "Timer.h"
#include "BHttpServer.h"
#include "Seq.h"
#include "Prober.h"
#include "BTcpClientPool.h"


class Proc
{
public:
	Proc(muduo::net::EventLoop& loop, const std::string& config_file);
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

	Seq _seq;
	Log _log;
	Config _config;
	ServiceConfig _sc;
	Prober _prober;
	BTcpClientPool _tcp_client_pool;

	Timer _timer;
	BHttpServer _http_server;
	
	muduo::net::EventLoop& _loop;
};