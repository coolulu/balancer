#include "Proxy.h"

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid();

	EventLoop loop;

	muduo::net::InetAddress listenAddr(10001);
	Proxy proxy(&loop, listenAddr);
	proxy.start();

	loop.loop();

	return 0;
}
