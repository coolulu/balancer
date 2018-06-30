#pragma once

#include <muduo/net/TcpClient.h>
#include <list>
#include "Session.h"
#include "Codec.h"

class Client
{
public:
	Client(	muduo::net::EventLoop* loop,
			const muduo::net::InetAddress& listenAddr,
			Session& session);

	void connect(); 
	void send(SessionID clientSeesonID, const muduo::string& msg);

private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);

	void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time);

	void onStringMessage(const muduo::net::TcpConnectionPtr& conn,
				const muduo::string& message,
				muduo::Timestamp time);

private:
    muduo::net::TcpClient _client;
	std::list<SessionID> _listSessionID;
	std::list<muduo::string> _listMsg;
	Session& _session;
	Codec _codec;
};

