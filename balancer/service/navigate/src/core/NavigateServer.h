#pragma once

#include <vector>

#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/EventLoopThreadPool.h>
#include "muduo/base/Mutex.h"

#include "CountLoad.h"

class Proc;

class NavigateServer
{
public:
	NavigateServer(Proc& proc, unsigned int index, muduo::net::EventLoop* loop);
	~NavigateServer();

public:
	void on_http_request(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void ready_destroy();
	void destroy();

	void update_load_result(const LoadResult& load_result);

public:
	Proc& _proc;
	unsigned int _index;
	muduo::net::HttpServer _http_server;

	muduo::MutexLock _mutex_load_result;
	LoadResult _load_result;
};

class NavigatePool
{
public:
	NavigatePool(Proc& proc);
	~NavigatePool();

public:
	void start();
	
public:
	Proc& _proc;
	int _thread_size;
	muduo::net::EventLoopThreadPool* _p_event_loop_thread_pool;
	std::vector<NavigateServer*> _navigate_server_vector;
};
