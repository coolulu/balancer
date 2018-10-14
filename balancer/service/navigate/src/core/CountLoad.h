#pragma once

#include <map>

#include "config/ServiceConfig.h"

class Proc;

class LoadProc
{
public:
	LoadProc();
	LoadProc(unsigned short service_id, const ServiceConfig::IPInfo& ip_info, int load_val);
	~LoadProc();

public:
	unsigned short _service_id;
	ServiceConfig::IPInfo _ip_info;
	int _load_val;
};

class LoadService
{
public:
	LoadService(unsigned short service_id);
	~LoadService();

public:
	unsigned short _service_id;
	std::map<unsigned int, LoadProc> _proc_map;
};

class LoadResult
{
public:
	LoadResult();
	~LoadResult();

public:
	bool find(unsigned short service_id, LoadProc& load_proc);
	void print();
	
public:
	unsigned int _update_count;
	unsigned int _update_time;
	std::map<unsigned short, LoadProc> _map;
};

class CountLoad
{
public:
	CountLoad(Proc& proc);
	~CountLoad();

public:
	void update(unsigned short service_id, 
				unsigned int proc_id, 
				int load_val);	
	void check_inservice();
	void check_count();
	void count(unsigned int t_now);

private:
	Proc& _proc;
	bool _check;
	std::map<unsigned short, LoadService> _service_map;
	LoadResult _load_result;
};