#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpClient.h>

#include "config/ServiceConfig.h"
#include "Codec.h"
#include "handle/HandleClient.h"
#include "core/PacketStream.h"

class Proc;

class BTcpClient
{
public:
	BTcpClient(Proc& proc, const ServiceConfig::IPInfo& ip_info);
	~BTcpClient();

public:
	bool check_idle(unsigned int now);
	void connect(); 
	bool send_msg(PacketPtr& msg);
	bool send_stream(PacketStreamPtr& stream);
	bool reomve_msg_send_buffer(unsigned long long msg_seq_id);

private:
	void on_connection(const muduo::net::TcpConnectionPtr& conn);
	void on_message(const muduo::net::TcpConnectionPtr& conn,
					PacketPtr& packet_ptr,
					muduo::Timestamp time);
	void on_write_complete(const muduo::net::TcpConnectionPtr& conn);
	void on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len);

	void check_msg_send_buffer_reduce();
	void check_stream_send_buffer_reduce();
	
private:
	static int s_count;

private:
	Proc& _proc;

	bool _connect;
	ServiceConfig::IPInfo _ip_info;
	std::map<unsigned long long, PacketPtr> _msg_send_buffer;
	std::map<unsigned long long, PacketStreamPtr> _stream_send_buffer;

	muduo::net::TcpClient _tcp_client;

	unsigned int _create_time;
	unsigned int _update_time;

	Codec _codec;
	HandleClient _handle_client;
};

typedef boost::shared_ptr<BTcpClient> BTcpClientPtr;