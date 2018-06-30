#include "BTcpClientPool.h"
#include "Proc.h"

BTcpClientPool::BTcpClientPool(Proc& proc) : _proc(proc)
{

}

BTcpClientPool::~BTcpClientPool()
{

}

void BTcpClientPool::send_msg(const ServiceConfig::IPInfo& ip_info, const std::string& msg)
{
	auto it = _client_map.find(ip_info.key_ip_port);
	if(it != _client_map.end())
	{
		it->second->send_msg(msg);
		return;
	}

	B_LOG_INFO << "new client";
	BTcpClientPtr tcp_client_ptr(new BTcpClient(_proc, ip_info));
	_client_map.insert(std::make_pair(ip_info.key_ip_port, tcp_client_ptr));

	tcp_client_ptr->connect();
	tcp_client_ptr->send_msg(msg);
}

void BTcpClientPool::check_idle()
{
	unsigned int t_now = ::time(nullptr);
	for(auto it = _client_map.begin(); it != _client_map.end();)
	{
		bool b = it->second->check_idle(t_now);
		if(b)
		{
			_client_map.erase(it++); //触发主动关闭
		}
		else
		{
			it++;
		}
	}
}
