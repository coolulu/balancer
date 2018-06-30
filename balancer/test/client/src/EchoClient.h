#pragma once

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpClient.h>

#include <boost/bind.hpp>

#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class Proxy;



class EchoClient : boost::noncopyable
{
public:
	EchoClient(	EventLoop* loop, const InetAddress& listenAddr, 
				Proxy* pProxy, unsigned int seqProxyClient);
	~EchoClient();

	void connect();
	void shutdown();
	void send(const string& msg);

private:
	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime);


private:
	EventLoop* _loop;
	Proxy* _pProxy;
	TcpClient _client;

	bool _bConnect;
	bool _bShutdown;
	std::vector<string> _msgVector;

public:
	const unsigned int _seqProxyClient;
	
};