#pragma once

#include <map>
#include <muduo/net/TcpServer.h>

#include "Codec.h"
#include "handle/HandleServer.h"

class Proc;

struct Context
{
	Context(unsigned long long conn_seq_id);

	unsigned long long _conn_seq_id;
	unsigned int _create_time;
	unsigned int _update_time;
};

class BTcpServer
{
public:
	BTcpServer(Proc& proc);
	~BTcpServer();

public:
	void start();
	bool send_msg(const muduo::net::TcpConnectionPtr& conn, PacketPtr& msg);
	bool send_stream(PacketPtr& msg);

private:
	void on_connection(const muduo::net::TcpConnectionPtr& conn);
	void on_message(const muduo::net::TcpConnectionPtr& conn,
					PacketPtr& packet_ptr,
					muduo::Timestamp time);
	void on_write_complete(const muduo::net::TcpConnectionPtr& conn);
	void on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len);

	void on_check_idle();

private:
	Proc& _proc;
	muduo::net::TcpServer* _p_tcp_server;
	std::map<unsigned long long, muduo::net::TcpConnectionPtr> _conn_map;

	Codec _codec;
	HandleServer _handle_server;
};
