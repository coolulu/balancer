#include "Session.h"

#include <muduo/base/Logging.h>
#include "TcpContext.h"

Session::Session() 
	: _sessionCount(EN_SESSION_ID_NULL)
{

}

Session::~Session()
{

}

SessionID Session::getSessionID()
{
	return ++_sessionCount != EN_SESSION_ID_NULL ? _sessionCount : ++_sessionCount;
}

muduo::net::TcpConnectionPtr Session::findClientTcpConnection(SessionID clientSessionID)
{
	auto it = _mapClient.find(clientSessionID);
	return it != _mapClient.end() ? it->second : nullptr;
}

SessionID Session::findClientSessionID(SessionID serviceSessionID)
{
	auto it = _mapService.find(serviceSessionID);
	return it != _mapService.end() ? it->second : EN_SESSION_ID_NULL;
}

void Session::insertClientTcpConnection(SessionID clientSessionID, muduo::net::TcpConnectionPtr tcpConnectionPtr)
{
	_mapClient.insert(std::make_pair(clientSessionID, tcpConnectionPtr));
}

void Session::insertClientSessionID(SessionID serviceSessionID, SessionID clientSessionID)
{
	_mapService.insert(std::make_pair(serviceSessionID, clientSessionID));
}

void Session::removeClientTcpConnection(SessionID clientSessionID)
{
	_mapClient.erase(clientSessionID);
}

void Session::removeClientSessionID(SessionID serviceSessionID)
{
	_mapService.erase(serviceSessionID);
}

void Session::checkTimeout(muduo::Timestamp& now)
{
	for(auto it = _mapClient.begin(); it != _mapClient.end(); it++)
	{
		muduo::net::TcpConnectionPtr& tcpConnectionPtr = it->second;
		if(tcpConnectionPtr)
		{
			TcpContextPtr tcpContextPtr(boost::any_cast<TcpContextPtr>(tcpConnectionPtr->getContext()));
			double d = timeDifference(now, tcpContextPtr->_updateTime);
			//if(d > 10)
			if(d > 1000)
			{
				_vectorTimeoutID.push_back(it->first);
				tcpConnectionPtr->shutdown(); // 关闭连接
			}
		}
		else
		{
			LOG_WARN << "tcpConnectionPtr is NULL";
			_vectorTimeoutID.push_back(it->first);
		}
	}

	
	if(_vectorTimeoutID.empty())
	{
		LOG_INFO << "_vectorTimeoutID is empty";
	}
	else
	{
		LOG_INFO << "_vectorTimeoutID.size: " << _vectorTimeoutID.size();		
		for(auto it = _vectorTimeoutID.begin(); it != _vectorTimeoutID.end(); it++)
		{
			removeClientTcpConnection(*it);	//清理超时id
		}
		_vectorTimeoutID.clear();
	}
}
