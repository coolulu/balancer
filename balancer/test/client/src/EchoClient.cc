#include "EchoClient.h"
#include "Proxy.h"

EchoClient::EchoClient(EventLoop* loop, 
							 const InetAddress& listenAddr, 
							 Proxy* pProxy,
							 unsigned int seqProxyClient)
	: _loop(loop),
	_client(loop, listenAddr, "EchoClient"), 
	_pProxy(pProxy),
	_seqProxyClient(seqProxyClient),
	_bConnect(false),
	_bShutdown(false)
{
	_client.setConnectionCallback(
		boost::bind(&EchoClient::onConnection, this, _1));
	_client.setMessageCallback(
		boost::bind(&EchoClient::onMessage, this, _1, _2, _3));
}

EchoClient::~EchoClient()
{
	if(_client.connection()->connected())
	{
		LOG_INFO << "shutdown client seqConnShell: " << _seqProxyClient;
		_client.disconnect();
	}
}

void EchoClient::connect()
{
	_client.connect();
}

void EchoClient::shutdown()
{
	_bShutdown = true;
//	_client.connection()->shutdown();
}

void EchoClient::send(const string& msg)
{
	if(_bConnect)
	{
		LOG_INFO << "send msg: " << msg;
		_client.connection()->send(msg);
	}
	else
	{
		LOG_INFO << "push_back msg: " << msg;
		_msgVector.push_back(msg);
	}
}

void EchoClient::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << conn->localAddress().toIpPort() << " -> "
		<< conn->peerAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN");

	_bConnect = conn->connected();
	if(conn->connected())
	{
		LOG_INFO << "_msgVector.size:" << _msgVector.size(); 
		for(unsigned int i = 0; i != _msgVector.size(); i++)
		{
			LOG_INFO << "send msg: " << _msgVector[i];
			conn->send(_msgVector[i]);
		}
		_msgVector.clear();
	}
	else
	{
		if(_bShutdown)
		{
			LOG_INFO << conn->name() << " proxy client DOWN";
		}
		else
		{
			LOG_INFO << conn->name() << " echo server DOWN, reconnect ...";
			connect();
		}
	}
}

void EchoClient::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime)
{
	muduo::string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
		<< "data received at " << receiveTime.toString();
	_pProxy->getLocate(_seqProxyClient)->send(msg);
}






