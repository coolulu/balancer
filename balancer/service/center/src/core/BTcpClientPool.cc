#include "BTcpClientPool.h"
#include "Proc.h"

BTcpClientPool::BTcpClientPool(Proc& proc) : _proc(proc)
{

}

BTcpClientPool::~BTcpClientPool()
{

}
/*
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

void BTcpClientPool::send_msg(const ServiceConfig::IPInfo& ip_info, const ::google::protobuf::Message& msg)
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

void BTcpClientPool::send_msg(const ServiceConfig::IPInfo& ip_info, 
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
							  const ::google::protobuf::Message& msg)
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
*/
BTcpClientPtr BTcpClientPool::get_client(const ServiceConfig::IPInfo& ip_info)
{
	auto it = _client_map.find(ip_info.key_ip_port);
	if(it != _client_map.end())
	{
		return it->second;
	}

	B_LOG_INFO	<< "new client"
				<< ", proc_id=" << ip_info.proc_id
				<< ", proc_des=" << ip_info.proc_des
				<< ", in_ip=" << ip_info.in_ip
				<< ", out_ip=" << ip_info.out_ip
				<< ", port=" << ip_info.port;

	BTcpClientPtr tcp_client_ptr(new BTcpClient(_proc, ip_info));
	_client_map.insert(std::make_pair(ip_info.key_ip_port, tcp_client_ptr));
	tcp_client_ptr->connect();
	return tcp_client_ptr;
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


