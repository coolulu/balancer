#pragma once

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include "Client.h"
#include "Session.h"


class Server
{
public:
	Server(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr);

	void start(); 

private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);

	void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time);

	void checkTimeout();

private:
	muduo::net::EventLoop* _pEventLoop;
    muduo::net::TcpServer _server;

	muduo::net::InetAddress _serviceAddr;
	Client* _pClient;

	Session _session;
};

