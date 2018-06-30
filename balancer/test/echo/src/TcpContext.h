#pragma once

#include <boost/shared_ptr.hpp>
#include <muduo/base/Timestamp.h>
#include "SesssionID.h"

class TcpContext
{
public:
	TcpContext();
	~TcpContext();

public:
	SessionID _sessionID;
	muduo::Timestamp _beginTime;
	muduo::Timestamp _updateTime;
	muduo::Timestamp _wakeUpTime;
};

typedef boost::shared_ptr<TcpContext> TcpContextPtr;
