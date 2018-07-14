#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpClient.h>

#include "ServiceConfig.h"
#include "Codec.h"

class Proc;

class BTcpClient
{
public:
	BTcpClient(Proc& proc, const ServiceConfig::IPInfo& ip_info);
	~BTcpClient();

public:
	bool check_idle(unsigned int now);
	void connect(); 
	void send_msg(PacketPtr& msg);

private:
	void on_connection(const muduo::net::TcpConnectionPtr& conn);
	void on_message(const muduo::net::TcpConnectionPtr& conn,
					PacketPtr& packet_ptr,
					muduo::Timestamp time);
	void on_write_complete(const muduo::net::TcpConnectionPtr& conn);
	void on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len);

	void check_send_buffer_reduce();
	
private:
	static int s_count;

private:
	Proc& _proc;

	bool _connect;
	ServiceConfig::IPInfo _ip_info;
	std::vector<PacketPtr> _msg_send_buffer;

	muduo::net::TcpClient _tcp_client;

	unsigned int _create_time;
	unsigned int _update_time;

	Codec _codec;
};

typedef boost::shared_ptr<BTcpClient> BTcpClientPtr;