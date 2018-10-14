#include "CountLoad.h"

#include "Proc.h"
#include "protocol/Protocol.h"

LoadProc::LoadProc() : _service_id(0), _load_val(-1)
{

}

LoadProc::LoadProc(unsigned short service_id, const ServiceConfig::IPInfo& ip_info, int load_val)
	:	_service_id(service_id), _ip_info(ip_info), _load_val(load_val)
{

}

LoadProc::~LoadProc()
{

}

LoadService::LoadService(unsigned short service_id)
	:	_service_id(service_id)
{

}

LoadService::~LoadService()
{

}

LoadResult::LoadResult()
	:	_update_count(0),
		_update_time(0)
{

}

LoadResult::~LoadResult()
{

}

bool LoadResult::find(unsigned short service_id, LoadProc& load_proc)
{
	auto it = _map.find(service_id);
	if(it != _map.end())
	{
		load_proc = it->second;
		return true;
	}

	return false;
}

void LoadResult::print()
{
	B_LOG_INFO	<< "_update_count=" << _update_count << ", _update_time=" << _update_time;
	if(_map.empty())
	{
		B_LOG_WARN << "_map is empty";
	}
	else
	{
		for(auto it : _map)
		{
			LoadProc& load_proc = it.second;
			B_LOG_INFO	<< "_service_id=" << load_proc._service_id
						<< ", proc_id=" << load_proc._ip_info.proc_id
						<< ", proc_id=" << load_proc._ip_info.proc_des
						<< ", proc_id=" << load_proc._ip_info.in_ip
						<< ", proc_id=" << load_proc._ip_info.in_port
						<< ", proc_id=" << load_proc._ip_info.out_ip
						<< ", proc_id=" << load_proc._ip_info.out_port
						<< ", _load_val=" << load_proc._load_val;
		}
	}
}

CountLoad::CountLoad(Proc& proc)
	:	_proc(proc),
		_check(false)
{

}

CountLoad::~CountLoad()
{

}

void CountLoad::update(unsigned short service_id, unsigned int proc_id, int load_val)
{
	ServiceConfig::IPInfo* ip_info = _proc._is.get_ip_info(service_id, proc_id);
	if(ip_info == nullptr)
	{
		B_LOG_WARN	<< "get_ip_info is not find, service_id= " << service_id
					<< ", proc_id=" << proc_id;
		return;
	}

	auto it_service_map = _service_map.find(service_id);
	if(it_service_map == _service_map.end())
	{
		// 新增LoadService
		LoadProc load_proc(service_id, *ip_info, load_val);

		LoadService load_service(service_id);
		load_service._proc_map.insert(std::make_pair(load_proc._ip_info.proc_id, load_proc));
		
		_service_map.insert(std::make_pair(load_service._service_id, load_service));
	}
	else
	{
		// 刷新覆盖LoadProc
		LoadService& load_service = it_service_map->second;

		LoadProc load_proc(service_id, *ip_info, load_val);
		load_service._proc_map[load_proc._ip_info.proc_id] = load_proc;
	}

	_check = true;
}

void CountLoad::check_inservice()
{
	B_LOG_INFO;
	bool b = false;

	for(auto& it_service_map : _service_map)
	{
		LoadService& load_service = it_service_map.second;

		std::vector<unsigned int> not_find_proc_vec;
		for(auto& it_proc_map : load_service._proc_map)
		{
			LoadProc& load_proc = it_proc_map.second;
			auto p = _proc._is.get_ip_info(load_proc._service_id, load_proc._ip_info.proc_id);
			if(p == nullptr)
			{
				// 不可服务的ip_info
				not_find_proc_vec.push_back(load_proc._ip_info.proc_id);
			}
		}

		if(not_find_proc_vec.size() > 0)
		{
			b = true;
			for(auto proc_id : not_find_proc_vec)
			{
				load_service._proc_map.erase(proc_id);
			}
		}
	}

	if(b)
	{
		unsigned int t_now = ::time(nullptr);
		count(t_now);
	}
}

void CountLoad::check_count()
{
	if(_check)
	{
		unsigned int t_now = ::time(nullptr);
		if(t_now - _load_result._update_time >= _proc._config.proc.count_load_check_gap)
		{
			count(t_now);
		}

		_check = false;
	}
}

void CountLoad::count(unsigned int t_now)
{
	++_load_result._update_count;
	_load_result._update_time = t_now;

	// 算出每个depend_service最少负载的proc_id
	auto p = _proc._sc.get_service(service::NAVIGATE);
	if(p == nullptr)
	{
		B_LOG_ERROR << "_sc.get_service(service::NAVIGATE) is nullptr";
		return;
	}

	//防止depend_service变化，导致已经过时的多余depend_service在_result_map里
	_load_result._map.clear();

	for(auto it = p->depend_map.begin(); it != p->depend_map.end(); it++)
	{
		unsigned short depend_service_id = it->second.depend_service_id;

		auto it_service_map = _service_map.find(depend_service_id);
		if(it_service_map != _service_map.end())
		{
			LoadService& load_service = it_service_map->second;
			if(load_service._proc_map.empty())
			{
				auto p = _proc._is.get_ip_info(depend_service_id);
				if(p != nullptr)
				{
					_load_result._map[depend_service_id] = LoadProc(depend_service_id, *p, -1);
				}
			}
			else
			{
				LoadProc& low = load_service._proc_map.begin()->second;
				for(auto it : load_service._proc_map)
				{
					LoadProc& load_proc = it.second;
					if(load_proc._load_val < low._load_val)
					{
						low = load_proc;
					}
				}

				_load_result._map[low._service_id] = low;
			}
		}
		else
		{
			auto p = _proc._is.get_ip_info(depend_service_id);
			if(p != nullptr)
			{
				_load_result._map[depend_service_id] = LoadProc(depend_service_id, *p, -1);
			}
		}
	}

	_load_result.print();

	// 更新到每个NavigateServer
	
	for(auto p_navigate_server : _proc._navigate_pool._navigate_server_vector)
	{
		if(p_navigate_server != nullptr)
		{
			p_navigate_server->update_load_result(_load_result);
		}
	}
}






