#pragma once

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind.hpp>

#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class EchoClient;
typedef boost::shared_ptr<EchoClient> EchoClientPtr;

class Proxy
{
	
public:
	Proxy(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr);
	
	void start();
	string& get_msg();
	muduo::net::TcpConnectionPtr getLocate(unsigned int seq);

private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);

	void onMessage(const muduo::net::TcpConnectionPtr& conn,
		muduo::net::Buffer* buf,
		muduo::Timestamp time);

private:
	muduo::net::TcpServer _server;
	InetAddress _serverAddr;
	string _msg;

	std::map<unsigned int, muduo::net::TcpConnectionPtr> _mapBack;
	std::map<muduo::net::TcpConnectionPtr, EchoClientPtr> _mapLocate;
	unsigned int _seq;
};