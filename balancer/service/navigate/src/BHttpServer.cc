#include "BHttpServer.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "Log.h"

BHttpServer::BHttpServer(Proc& proc) : _proc(proc), _p_http_server(nullptr)
{

}

BHttpServer::~BHttpServer()
{
	if(_p_http_server == nullptr)
	{
		delete _p_http_server;
		_p_http_server = nullptr;
	}
}

void BHttpServer::start()
{
	if(_p_http_server == nullptr)
	{
		_p_http_server = new muduo::net::HttpServer(&_proc._loop, 
			muduo::net::InetAddress(_proc._config.net.http.ip, _proc._config.net.http.port), "HttpServer");
		_p_http_server->setHttpCallback(boost::bind(&BHttpServer::on_http_request, this, _1, _2));
		_p_http_server->start();
	}
}

void BHttpServer::on_http_request(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
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


