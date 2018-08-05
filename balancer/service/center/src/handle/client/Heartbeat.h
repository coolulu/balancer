#pragma once

#include "core/TaskMsgPool.h"
#include "config/ServiceConfig.h"

class Proc;

class Heartbeat : public TaskMsgBase
{
public:
	Heartbeat(Proc& proc, 
			  unsigned int gap_us,
			  unsigned short service_id,
			  const ServiceConfig::IPInfo& ip_info);
	virtual ~Heartbeat();

public:
	enum
	{
		EN_STATE_REQUEST = 10,
		EN_STATE_RESPONSE = 20,
	};

public:
	virtual int timeout();
	virtual int run(void* p = nullptr);
	virtual void print(const std::string& prefix = "");

	int on_request();
	int on_response(void* p);

private:
	unsigned short _service_id;
	ServiceConfig::IPInfo _ip_info;

};