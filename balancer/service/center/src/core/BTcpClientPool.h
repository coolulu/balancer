#pragma once

#include <map>
#include "BTcpClient.h"
#include "config/ServiceConfig.h"
#include <google/protobuf/message.h>

class Proc;
class BTcpClient;

class BTcpClientPool
{
public:
	BTcpClientPool(Proc& proc);
	~BTcpClientPool();

public:
	/*
	void send_msg(const ServiceConfig::IPInfo& ip_info, const std::string& msg);
	void send_msg(const ServiceConfig::IPInfo& ip_info, const ::google::protobuf::Message& msg);
	void send_msg(const ServiceConfig::IPInfo& ip_info, 
				  unsigned short version,
				  unsigned short from_service_id,
				  unsigned short to_service_id,
				  unsigned int to_proc_id,
				  unsigned int app_id,
				  unsigned int app_version,
				  unsigned long long conn_seq_id,
				  unsigned long long msg_seq_id,
				  unsigned char data_format,
				  unsigned char reserve_field_0,
				  unsigned int reserve_field_1,
				  unsigned int reserve_field_2,
				  unsigned int reserve_field_3,
				  const ::google::protobuf::Message& msg);
	*/
	BTcpClientPtr get_client(const ServiceConfig::IPInfo& ip_info);
	void check_idle();

public:
	// key_ip_portµ½ClientµÄÓ³Éä
	std::map<unsigned long long, BTcpClientPtr> _client_map;
	Proc& _proc;
};