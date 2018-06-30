#pragma once

#include <map>
#include "BTcpClient.h"
#include "ServiceConfig.h"

class Proc;
class BTcpClient;

class BTcpClientPool
{
public:
	BTcpClientPool(Proc& proc);
	~BTcpClientPool();

public:
	void send_msg(const ServiceConfig::IPInfo& ip_info, const std::string& msg);
	void check_idle();

public:
	// key_ip_portµ½ClientµÄÓ³Éä
	std::map<unsigned long long, BTcpClientPtr> _client_map;
	Proc& _proc;
};