#pragma once

#include <vector>
#include <map>

#include "config/ServiceConfig.h"

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
	InserviceService() : _is_ok(false){}
	~InserviceService(){}

public:
	inline void assign(const InserviceService& is){*this = is;}

	// ��������ip�б��Ƿ���ã���������ܾ�����
	inline bool is_ok(){return _is_ok;}

	// �ñ������service_id�õ�����service_id,������������ipinfo
	bool load_ip_info(unsigned short service_id, ServiceConfig& sc);
	bool get_ip_info(unsigned short depend_service_id, ServiceConfig::IPInfo& ip_info);
	bool get_ip_info(unsigned short depend_service_id, unsigned int proc_id, ServiceConfig::IPInfo& ip_info);
	InserviceList* get_inservice_list(unsigned short depend_service_id);

private:
	bool _is_ok;
	std::map<unsigned short, InserviceList> _map;
	

};
