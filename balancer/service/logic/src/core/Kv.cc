#include "Kv.h"

#include "log/Log.h"
#include "tool/Util.h"

Kv::Kv()
{

}

Kv::~Kv()
{

}

bool Kv::load_kv(std::map<std::string, ServiceConfig::KV>& kv_map)
{
	bool b = true;


	return b;
}

void Kv::get_str(std::map<std::string, ServiceConfig::KV>& kv_map,
				 const std::string& key, 
				 std::string& str,
				 bool& b)
{
	auto it = kv_map.find(key);
	if(it == kv_map.end())
	{
		b = false;
		B_LOG_ERROR << "kv str, key is not find, key=" << key;
		return;
	}

	if(it->second.val.empty())
	{
		b = false;
		B_LOG_ERROR << "kv str, val is empty, key=" << key;
		return;
	}

	str = it->second.val;
	B_LOG_ERROR << "kv str, success, key=" << key << ", val=" << it->second.val << ", str=" << str;
}

void Kv::get_uint(std::map<std::string, ServiceConfig::KV>& kv_map,
				  const std::string& key, 
				  unsigned int& i,
				  bool& b)
{
	auto it = kv_map.find(key);
	if(it == kv_map.end())
	{
		b = false;
		B_LOG_ERROR << "kv uint, key is not find, key=" << key;
		return;
	}

	if(it->second.val.empty())
	{
		b = false;
		B_LOG_ERROR << "kv uint, val is empty, key=" << key;
		return;
	}

	for(auto c :  it->second.val)
	{
		if(c < '0' || c > '9')
		{
			b = false;
			B_LOG_ERROR << "kv uint, val is not number, key=" << key << ", val=" << it->second.val;
			return;
		}
	}

	i = Util::str_2_uint(it->second.val);
	B_LOG_ERROR << "kv uint, success, key=" << key << ", val=" << it->second.val << ", i=" << i;
}

void Kv::get_uint(std::map<std::string, ServiceConfig::KV>& kv_map, 
				  const std::string& key, 
				  unsigned short& i, 
				  bool& b)
{
	auto it = kv_map.find(key);
	if(it == kv_map.end())
	{
		b = false;
		B_LOG_ERROR << "kv uint, key is not find, key=" << key;
		return;
	}

	if(it->second.val.empty())
	{
		b = false;
		B_LOG_ERROR << "kv uint, val is empty, key=" << key;
		return;
	}

	for(auto c :  it->second.val)
	{
		if(c < '0' || c > '9')
		{
			b = false;
			B_LOG_ERROR << "kv uint, val is not number, key=" << key << ", val=" << it->second.val;
			return;
		}
	}

	i = Util::str_2_ushort(it->second.val);
	B_LOG_ERROR << "kv uint, success, key=" << key << ", val=" << it->second.val << ", i=" << i;
}
