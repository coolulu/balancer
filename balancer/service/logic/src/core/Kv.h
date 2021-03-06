#pragma once

#include <string>

#include "config/ServiceConfig.h"

namespace KvKey
{
	static const std::string& task_msg_master_timeout_us	= "task_msg_master_timeout_us";
	static const std::string& task_msg_sub_timeout_us		= "task_msg_sub_timeout_us";
}

class Kv
{
public:
	Kv();
	~Kv();

public:
	bool load_kv(std::map<std::string, ServiceConfig::KV>& kv_map);

private:
	void get_str(std::map<std::string, ServiceConfig::KV>& kv_map,
				 const std::string& key, 
				 std::string& str,
				 bool& b);
	void get_uint(std::map<std::string, ServiceConfig::KV>& kv_map,
				  const std::string& key, 
				  unsigned int& i,
				  bool& b);

	void get_uint(std::map<std::string, ServiceConfig::KV>& kv_map,
				  const std::string& key, 
				  unsigned short& i,
				  bool& b);

public:
	unsigned int _task_msg_master_timeout_us;
	unsigned int _task_msg_sub_timeout_us;
};
