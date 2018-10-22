#pragma once

#include <map>
#include <muduo/net/TcpServer.h>

#include "Codec.h"
#include "handle/HandleGate.h"
#include "core/PacketStream.h"

class Proc;

struct GateContext
{
	GateContext(unsigned long long conn_seq_id);

	enum EN_CONN
	{
		EN_CONN_NOT_INIT_CONN	= 0,	// 客户端连接未获取conn_id
		EN_CONN_NOT_LOGIN		= 1,	// 客户端连接获取conn_id,未登录
		EN_CONN_LOGIN			= 2,	// 客户端连接获取conn_id,登录成功
	};

	unsigned long long _conn_seq_id;
	unsigned int _create_time;
	unsigned int _update_time;
	EN_CONN		 _en_conn;
	bool		 _is_send_login_request;	// 是否已发送登录请求
	bool		 _is_wake_heartbeat_wait;
};

class GateServer
{
public:
	GateServer(Proc& proc);
	~GateServer();

public:
	void start();
	bool send_msg(const muduo::net::TcpConnectionPtr& conn, PacketPtr& msg);
	bool send_stream(PacketPtr& msg);
	bool send_stream(PacketStreamPtr& stream);

private:
	void on_connection(const muduo::net::TcpConnectionPtr& conn);
	void on_message(const muduo::net::TcpConnectionPtr& conn,
					PacketPtr& packet_ptr,
					muduo::Timestamp time);
	void on_write_complete(const muduo::net::TcpConnectionPtr& conn);
	void on_high_water_mark(const muduo::net::TcpConnectionPtr& conn, size_t len);

	void on_check_idle();

public:
	bool find(unsigned long long conn_seq_id, muduo::net::TcpConnectionPtr& conn);
	void shutdown_all_conn();
	unsigned int conn_size();

private:
	Proc& _proc;
	muduo::net::TcpServer* _p_tcp_server;
	std::map<unsigned long long, muduo::net::TcpConnectionPtr> _conn_map;

	Codec _codec;
	HandleGate _handle_gate;
};
