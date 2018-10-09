#include "InserviceService.h"

InserviceList::InserviceList(unsigned short service_id, const std::vector<ServiceConfig::IPInfo>& il)
	: depend_service_id(service_id), count(0), inservice_list(il)
{
	for(auto& ip_info: inservice_list)
	{
		inservice_map.insert(std::make_pair(ip_info.proc_id, ip_info));
	}
}

bool InserviceService::load_ip_info(unsigned short service_id, ServiceConfig& sc)
{
	auto p = sc.get_service(service_id);
	if(p == nullptr)
	{
		return _is_ok = false;	//缺少本服务的配置
	}

	//遍历本服务的依赖服务ipinfo
	for(auto it = p->depend_map.begin(); it != p->depend_map.end(); it++)
	{
		auto p_depend_service = sc.get_service(it->second.depend_service_id);
		if(p_depend_service == nullptr || p_depend_service->inservice_list.empty())
		{
			return _is_ok = false; //没有依赖服务的ipinfo
		}

		_map.insert(std::make_pair(it->second.depend_service_id, 
			InserviceList(it->second.depend_service_id, p_depend_service->inservice_list)));
	}

	return _is_ok = true;
}

bool InserviceService::get_ip_info(unsigned short depend_service_id, ServiceConfig::IPInfo& ip_info)
{
	auto it = _map.find(depend_service_id);
	if(it != _map.end())
	{
		InserviceList& il = it->second;
		unsigned int size = il.inservice_list.size();
		if(size > 0)
		{
			unsigned int index = (++il.count) % size;
			ip_info = il.inservice_list[index];
			return true;
		}
	}

	return false;
}

bool InserviceService::get_ip_info(unsigned short depend_service_id, unsigned int proc_id, ServiceConfig::IPInfo& ip_info)
{
	auto it = _map.find(depend_service_id);
	if(it != _map.end())
	{
		InserviceList& il = it->second;
		auto it_ip_info = il.inservice_map.find(proc_id);
		if(it_ip_info != il.inservice_map.end())
		{
			ip_info = it_ip_info->second;
			return true;
		}
	}

	return false;
}

InserviceList* InserviceService::get_inservice_list(unsigned short depend_service_id)
{
	auto it = _map.find(depend_service_id);
	if(it != _map.end())
	{
		return &it->second;
	}

	return nullptr;
}


