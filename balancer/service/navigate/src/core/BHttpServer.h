#pragma once

#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>

class Proc;

class BHttpServer
{
public:
	BHttpServer(Proc& proc);
	~BHttpServer();

public:
	void start();

private:
	void on_http_request(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);

private:
	Proc& _proc;
	muduo::net::HttpServer* _p_http_server;
};