#pragma once

#include <vector>

#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/EventLoopThreadPool.h>

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

public:
	Proc& _proc;
	unsigned int _index;
	muduo::net::HttpServer _http_server;
};

class NavigatePool
{
public:
	NavigatePool(Proc& proc);
	~NavigatePool();

public:
	void start();
	
private:
	Proc& _proc;
	int _thread_size;
	muduo::net::EventLoopThreadPool* _p_event_loop_thread_pool;
	std::vector<NavigateServer*> _navigate_server_vector;
};
