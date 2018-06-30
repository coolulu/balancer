#pragma once

#include <unordered_map>
#include <vector>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>
#include "SesssionID.h"


class Session
{
public:
	Session();
	~Session();

public:
	SessionID getSessionID();

	muduo::net::TcpConnectionPtr findClientTcpConnection(SessionID clientSessionID);
	SessionID findClientSessionID(SessionID serviceSessionID);

	void insertClientTcpConnection(SessionID clientSessionID, muduo::net::TcpConnectionPtr tcpConnectionPtr);
	void insertClientSessionID(SessionID serviceSessionID, SessionID clientSessionID);

	void removeClientTcpConnection(SessionID clientSessionID);
	void removeClientSessionID(SessionID serviceSessionID);

	void checkTimeout(muduo::Timestamp& now);

private:
	SessionID _sessionCount;
	std::unordered_map<SessionID, muduo::net::TcpConnectionPtr> _mapClient;	// client SessionID -> client TcpConnectionPtr
	std::unordered_map<SessionID, SessionID> _mapService;	// service SessionID -> client SessionID
	std::vector<SessionID> _vectorTimeoutID;
};

