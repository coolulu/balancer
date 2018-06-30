#include "Client.h"

#include <muduo/base/Logging.h>
#include <boost/bind.hpp>
#include "TcpContext.h"


Client::Client(muduo::net::EventLoop* loop, 
			   const muduo::net::InetAddress& listenAddr,
			   Session& session)
	:	_client(loop, listenAddr, "Client"), 
		_session(session),
		_codec(boost::bind(&Client::onStringMessage, this, _1, _2, _3))
{
	_client.setConnectionCallback(
		boost::bind(&Client::onConnection, this, _1));
	//_client.setMessageCallback(
	//	boost::bind(&Client::onMessage, this, _1, _2, _3));
	_client.setMessageCallback(
		boost::bind(&Codec::onMessage, &_codec, _1, _2, _3));

	_client.enableRetry();
}

void Client::connect()
{
	_client.connect();
}

void Client::send(SessionID clientSeesonID, const muduo::string& msg)
{
	SessionID sessionID = _session.getSessionID();
	_listSessionID.push_back(sessionID);
	_session.insertClientSessionID(sessionID, clientSeesonID);
	LOG_INFO << "insertClientSessionID: "<< sessionID << " - " << clientSeesonID;

	for(auto& sessionID : _listSessionID)
	{
		LOG_WARN << "_listSessionID:" << sessionID;
	}

	muduo::net::TcpConnectionPtr tcpConnectionPtr = _client.connection();
	if(tcpConnectionPtr)
	{
		//tcpConnectionPtr->send(msg);
		_codec.send(get_pointer(tcpConnectionPtr), msg);
	}
	else
	{
		_listMsg.push_back(msg);
	}

}

void Client::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	LOG_INFO << "onConnection " << conn->name() << " " 
		<< conn->peerAddress().toIpPort() << " -> " 
		<< conn->localAddress().toIpPort() << " is " << (conn->connected() ? "UP" : "DOWN");
	
	if(conn->connected())
	{
		conn->setTcpNoDelay(true);
		if(_listMsg.empty())
		{
			LOG_INFO << "_listMsg is empty:";
		}
		else
		{
			LOG_INFO << "_listMsg.size:" << _listMsg.size();
			for(auto& msg : _listMsg)
			{
			//	conn->send(msg);
				_codec.send(get_pointer(conn), msg);
			}
			_listMsg.clear();
		}
	}
}

void Client::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time)
{
	muduo::string msg(buf->retrieveAllAsString());
	LOG_INFO << "onMessage " << conn->name() << " " 
		<< msg.size() << " bytes, " << "data received at " << time.toString() 
		<< " msg: " << msg;

	if(_listSessionID.empty())
	{
		LOG_WARN << "listSessionID is empty";
	}
	else
	{
		for(auto& sessionID : _listSessionID)
		{
			LOG_WARN << "_listSessionID:" << sessionID;
		}

		SessionID sessionID = _listSessionID.front();
		_listSessionID.pop_front();
		SessionID clientSessionID = _session.findClientSessionID(sessionID);
		_session.removeClientSessionID(sessionID);

		LOG_INFO << "sessionID:" << sessionID;
		LOG_INFO << "clientSessionID:" << clientSessionID;
		if(clientSessionID == EN_SESSION_ID_NULL)
		{
			LOG_WARN << "ClientSessionID is NULL";
		}
		else
		{
			muduo::net::TcpConnectionPtr tcpConnectionPtr = 
				_session.findClientTcpConnection(clientSessionID);
			if(tcpConnectionPtr)
			{
				tcpConnectionPtr->send(msg);
			}
			else
			{
				LOG_WARN << "conn is empty";
			}
		}
	}

}

void Client::onStringMessage(const muduo::net::TcpConnectionPtr& conn,
						     const muduo::string& message,
							 muduo::Timestamp time)
{
	muduo::string msg(message);
	LOG_INFO << "onMessage " << conn->name() << " " 
		<< msg.size() << " bytes, " << "data received at " << time.toString() 
		<< " msg: " << msg;

	if(_listSessionID.empty())
	{
		LOG_WARN << "listSessionID is empty";
	}
	else
	{
		for(auto& sessionID : _listSessionID)
		{
			LOG_WARN << "_listSessionID:" << sessionID;
		}

		SessionID sessionID = _listSessionID.front();
		_listSessionID.pop_front();
		SessionID clientSessionID = _session.findClientSessionID(sessionID);
		_session.removeClientSessionID(sessionID);

		LOG_INFO << "sessionID:" << sessionID;
		LOG_INFO << "clientSessionID:" << clientSessionID;
		if(clientSessionID == EN_SESSION_ID_NULL)
		{
			LOG_WARN << "ClientSessionID is NULL";
		}
		else
		{
			muduo::net::TcpConnectionPtr tcpConnectionPtr = 
				_session.findClientTcpConnection(clientSessionID);
			if(tcpConnectionPtr)
			{
				tcpConnectionPtr->send(msg);
			}
			else
			{
				LOG_WARN << "conn is empty";
			}
		}
	}

}


