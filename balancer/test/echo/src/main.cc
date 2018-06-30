#include "Server.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <unistd.h>

int main()
{
	LOG_INFO << "pid = " << getpid();
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(10000);
	Server server(&loop, listenAddr);
	server.start();
	loop.loop();

	return 0;
}

