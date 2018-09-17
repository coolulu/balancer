#include "BTcpClientPool.h"
#include "Proc.h"
#include "tool/Util.h"

BTcpClientPool::BTcpClientPool(Proc& proc) : _proc(proc)
{

}

BTcpClientPool::~BTcpClientPool()
{

}

BTcpClientPtr BTcpClientPool::get_client(const ServiceConfig::IPInfo& ip_info)
{
	auto it = _client_map.find(ip_info.key_in_ip_port);
	if(it != _client_map.end())
	{
		return it->second;
	}

	B_LOG_INFO	<< "new client"
				<< ", proc_id=" << ip_info.proc_id
				<< ", proc_des=" << ip_info.proc_des
				<< ", in_ip=" << ip_info.in_ip
				<< ", in_ip=" << ip_info.in_port
				<< ", out_ip=" << ip_info.out_ip
				<< ", out_port=" << ip_info.out_port;

	BTcpClientPtr tcp_client_ptr(new BTcpClient(_proc, ip_info));
	_client_map.insert(std::make_pair(ip_info.key_in_ip_port, tcp_client_ptr));
	tcp_client_ptr->connect();
	return tcp_client_ptr;
}

void BTcpClientPool::check_idle()
{
	unsigned long long now_us = Util::get_us();	
	unsigned int t_now = now_us / 1000 / 1000;

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


