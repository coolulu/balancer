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
			  unsigned long long service_update_time,
			  const ServiceConfig::IPInfo& ip_info);
	virtual ~Heartbeat();

public:
	static const std::string& s_task_name;

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
	int on_response();
	int on_timeout(const ServiceConfig::Heartbeat& heartbeat,
				   ServiceConfig::IPInfo& ip_info);

	void update_count();
	void on_count(const ServiceConfig::Heartbeat& heartbeat,
				  ServiceConfig::IPInfo& ip_info);
	void update_is_run(ServiceConfig::IPInfo& ip_info, bool is_run);
	bool is_inservice_list();
	void update_depend_service_time(const ServiceConfig::IPInfo& ip_info);

private:
	unsigned short _service_id;
	unsigned long long _service_update_time;
	ServiceConfig::IPInfo _ip_info;
	bool _is_update_conf;
	bool _is_send;
};