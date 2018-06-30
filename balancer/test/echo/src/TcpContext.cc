#include "TcpContext.h"

TcpContext::TcpContext()
	:	_sessionID(EN_SESSION_ID_NULL),
		_beginTime(muduo::Timestamp::now()),
		_updateTime(_beginTime),
		_wakeUpTime(_beginTime)
{

}

TcpContext::~TcpContext()
{

}
