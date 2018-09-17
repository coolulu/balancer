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
	BTcpClientPtr get_client(const ServiceConfig::IPInfo& ip_info);
	void check_idle();

public:
	// key_in_ip_portµ½ClientµÄÓ³Éä
	std::map<unsigned long long, BTcpClientPtr> _client_map;
	Proc& _proc;
};