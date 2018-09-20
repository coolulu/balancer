#include "NavigateServer.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "log/Log.h"
#include "tool/Util.h"

NavigateServer::NavigateServer(Proc& proc, unsigned int index, muduo::net::EventLoop* loop)
	:	_proc(proc), 
		_index(index), 
		_http_server(loop, 
					 muduo::net::InetAddress(_proc._config.net.navigate.ip, _proc._config.net.navigate.port),
					 "NavigateServer",
					 muduo::net::TcpServer::kReusePort)
{
	_http_server.setHttpCallback(boost::bind(&NavigateServer::on_http_request, this, _1, _2));
	_http_server.getLoop()->runInLoop(boost::bind(&muduo::net::HttpServer::start, &_http_server));
}

NavigateServer::~NavigateServer()
{

}

void NavigateServer::on_http_request(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	B_LOG_INFO << "_index=" << _index;
	B_LOG_INFO << "method=" << req.methodString();
	B_LOG_INFO << "path=" << req.path();
	B_LOG_INFO << "query=" << req.query();
	B_LOG_INFO << "receiveTime=" << req.receiveTime().toString();

	if(req.path() == "/about")
	{
		rsp->setStatusCode(muduo::net::HttpResponse::k200Ok);
		rsp->setStatusMessage("OK");
		rsp->setBody("{\"a\": 1, \"b\": 2}");
		rsp->setCloseConnection(true);
	}
	else
	{
		rsp->setStatusCode(muduo::net::HttpResponse::k404NotFound);
		rsp->setStatusMessage("Not Found");
		rsp->setCloseConnection(true);
	}
}

void NavigateServer::ready_destroy()
{
	// 不能跨线程释放,唤醒所在的线程再释放
	_http_server.getLoop()->runInLoop(boost::bind(&NavigateServer::destroy, this));
}

void NavigateServer::destroy()
{
	delete this;
}

NavigatePool::NavigatePool(Proc& proc)
	:	_proc(proc),
		_thread_size(::sysconf(_SC_NPROCESSORS_CONF))
{

}

NavigatePool::~NavigatePool()
{
	for(auto p_navigate_server :  _navigate_server_vector)
	{	
		p_navigate_server->ready_destroy();
		p_navigate_server = nullptr;
	}

	_navigate_server_vector.clear();

	if(_p_event_loop_thread_pool != nullptr)
	{
		delete _p_event_loop_thread_pool;
		_p_event_loop_thread_pool = nullptr;
	}
}

void NavigatePool::start()
{
	if(_p_event_loop_thread_pool == nullptr)
	{
		_p_event_loop_thread_pool = new muduo::net::EventLoopThreadPool(&_proc._loop, "NavigatePool");
		_p_event_loop_thread_pool->setThreadNum(_thread_size);
		_p_event_loop_thread_pool->start();
	}

	for(int i = 0; i != _thread_size; i++)
	{
		_navigate_server_vector.push_back(new NavigateServer(_proc, i, _p_event_loop_thread_pool->getNextLoop()));
	}
}

