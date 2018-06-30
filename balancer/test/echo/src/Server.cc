#include "Server.h"

#include <muduo/base/Timestamp.h>
#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
#include "Session.h"
#include "TcpContext.h"


Server::Server(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr)
	:	_pEventLoop(loop),
		_server(loop, listenAddr, "Server"),
		_pClient(nullptr), 
		_serviceAddr("120.79.137.155", 2007)	// echo server
{
	_server.setConnectionCallback(
		boost::bind(&Server::onConnection, this, _1));
	_server.setMessageCallback(
		boost::bind(&Server::onMessage, this, _1, _2, _3));
//	_pEventLoop->runEvery(1.0, boost::bind(&Server::checkTimeout, this));
}

void Server::start()
{
	LOG_INFO << _server.name();
	_server.start();
}

void Server::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	LOG_INFO << "onConnection " << conn->name() << " " 
		<< conn->peerAddress().toIpPort() << " -> " 
		<< conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");

	if(conn->connected())
	{
		conn->setTcpNoDelay(true);

		TcpContextPtr tcpContextPtr(new TcpContext());
		tcpContextPtr->_sessionID = _session.getSessionID();
		_session.insertClientTcpConnection(tcpContextPtr->_sessionID, conn);
		conn->setContext(tcpContextPtr);

		LOG_INFO << "insert client sessionID:" << tcpContextPtr->_sessionID;
	}
	else
	{
		if(conn->getContext().empty())
		{
			LOG_WARN << "conn getContext is empty";
		}
		else
		{
			TcpContextPtr tcpContextPtr(boost::any_cast<TcpContextPtr>(conn->getContext()));
			_session.removeClientTcpConnection(tcpContextPtr->_sessionID);

			LOG_INFO << "insert client sessionID:" << tcpContextPtr->_sessionID;
		}
	}
	 
}

void Server::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time)
{
  muduo::string msg(buf->retrieveAllAsString());
  LOG_INFO << "onMessage " << conn->name() << " " 
	  << msg.size() << " bytes, " << "data received at " << time.toString() 
	  << " msg: " << msg;
 
  if(conn->getContext().empty())
  {
	  LOG_WARN << "conn getContext is empty";
  }
  else
  {
	  if(_pClient == NULL)
	  {
		  _pClient = new Client(conn->getLoop(), _serviceAddr, _session);
		  _pClient->connect();
	  }

	  TcpContextPtr tcpContextPtr(boost::any_cast<TcpContextPtr>(conn->getContext()));
	  tcpContextPtr->_wakeUpTime = time;
	  tcpContextPtr->_updateTime = muduo::Timestamp::now();
	  _pClient->send(tcpContextPtr->_sessionID, msg);
  }

}

void Server::checkTimeout()
{
	muduo::Timestamp now = muduo::Timestamp::now();
	LOG_INFO << now.microSecondsSinceEpoch();
	_session.checkTimeout(now);
}


