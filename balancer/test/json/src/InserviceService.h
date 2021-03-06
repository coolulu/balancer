#pragma once

#include <vector>
#include <map>

#include "ServiceConfig.h"

struct InserviceList
{
	InserviceList(unsigned short service_id, const std::vector<ServiceConfig::IPInfo>& il);

	unsigned short depend_service_id;
	unsigned int count;
	std::vector<ServiceConfig::IPInfo> inservice_list;
	std::map<unsigned int, ServiceConfig::IPInfo> inservice_map;
};

class InserviceService
{
public:
	InserviceService(){}
	~InserviceService(){}

public:
	inline void assign(const InserviceService& is){*this = is;}

	// 用本服务的service_id拿到依赖service_id,加载依赖服务ipinfo
	bool load_ip_info(unsigned short service_id, ServiceConfig& sc);
	bool get_ip_info(unsigned short depend_service_id, ServiceConfig::IPInfo& ip_info);
	bool get_ip_info(unsigned short depend_service_id, unsigned int proc_id, ServiceConfig::IPInfo& ip_info);

private:
	std::map<unsigned short, InserviceList> _map;

};
