#include "Proxy.h"
#include "EchoClient.h"

Proxy::Proxy(muduo::net::EventLoop* loop, 
			 const muduo::net::InetAddress& listenAddr)
			 :	_server(loop, listenAddr, "EchoServer"), 
			 _serverAddr("120.79.137.155", 2007), 
			 //_serverAddr("220.181.57.216", 80), //baidu
			 _seq(0)
{
	_server.setConnectionCallback(
		boost::bind(&Proxy::onConnection, this, _1));
	_server.setMessageCallback(
		boost::bind(&Proxy::onMessage, this, _1, _2, _3));
}

void Proxy::start()
{
	_server.start();
}

string& Proxy::get_msg()
{
	return _msg;
}

muduo::net::TcpConnectionPtr Proxy::getLocate(unsigned int seq)
{
	return _mapBack[seq];
}

void Proxy::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
		<< conn->localAddress().toIpPort() << " is "
		<< (conn->connected() ? "UP" : "DOWN");
	if(!conn->connected())
	{
		std::map<muduo::net::TcpConnectionPtr, EchoClientPtr>::iterator it = _mapLocate.find(conn);
		if(it != _mapLocate.end())
		{
			it->second->shutdown();
			_mapBack.erase(it->second->_seqProxyClient);
		}
		_mapLocate.erase(it);
	}

	LOG_INFO << "_mapBack.size:" << _mapBack.size();
	LOG_INFO << "_mapLocate.size:" << _mapLocate.size();
}

void Proxy::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time)
{
	_msg = buf->retrieveAllAsString();
	LOG_INFO << conn->name() << " echo " << _msg.size() << " bytes, "
		<< "data received at " << time.toString();

	std::map<muduo::net::TcpConnectionPtr, EchoClientPtr>::iterator it = _mapLocate.find(conn);
	if(it == _mapLocate.end())
	{
		++_seq;
		EchoClientPtr client(new EchoClient(conn->getLoop(), _serverAddr, this, _seq));
		client->send(_msg);
		_mapLocate.insert(std::make_pair(conn, client));
		_mapBack.insert(std::make_pair(_seq, conn));
		client->connect();
	}
	else
	{
		it->second->send(_msg);	
	}

}





