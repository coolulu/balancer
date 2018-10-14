#pragma once

#include <string>

#include "config/ServiceConfig.h"

namespace KvKey
{
	static const std::string& navigate_key = "navigate_key";
	static const std::string& navigate_key_timeout_us = "navigate_key_timeout_us";
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

public:
	std::string _navigate_key;
	unsigned int _navigate_key_timeout_us;
};