﻿#include "ServiceConfig.h"

#include <algorithm>
#include <set>
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "tool/Util.h"

std::string ServiceConfig::json_to_map(const std::string& json)
{
	rapidjson::Document document;
	document.Parse(json.c_str());
	if(!document.IsObject())
		return err_is_not_object(json);

	if(!document.HasMember(KeyServiceConfig::service_map.c_str()))
		return err_is_not_array(KeyServiceConfig::service_map);
	const rapidjson::Value& v = document[KeyServiceConfig::service_map.c_str()];
	if(!v.IsArray())
		return err_is_not_array(KeyServiceConfig::service_map);

	std::set<std::string> check_service_name;
	const auto& array = v.GetArray();
	for(const auto& a : array)
	{
		Service service;
		if(!get_uint(a, KeyServiceConfig::service_id, service.service_id))
			return err_is_not_uint(KeyServiceConfig::service_id, service.service_name);
		if(!get_string(a, KeyServiceConfig::service_name, service.service_name))
			return err_is_not_string(KeyServiceConfig::service_name, service.service_name);

		check_service_name.insert(service.service_name);

		{
			if(!a.HasMember(KeyServiceConfig::heartbeat.c_str()))
				return err_is_not_object(KeyServiceConfig::heartbeat);
			const rapidjson::Value& cv = a[KeyServiceConfig::heartbeat.c_str()];
			if(!cv.IsObject())
				return err_is_not_object(KeyServiceConfig::heartbeat, service.service_name);

			if(!get_bool(cv, KeyServiceConfig::heartbeat_enable, service.heartbeat.heartbeat_enable))
				return err_is_not_uint(KeyServiceConfig::heartbeat_enable, service.service_name);
			if(!get_uint(cv, KeyServiceConfig::heartbeat_gap, service.heartbeat.heartbeat_gap))
				return err_is_not_uint(KeyServiceConfig::heartbeat_gap, service.service_name);
			if(!get_uint(cv, KeyServiceConfig::lose_time, service.heartbeat.lose_time))
				return err_is_not_uint(KeyServiceConfig::lose_time, service.service_name);
			if(!get_uint(cv, KeyServiceConfig::recover_time, service.heartbeat.recover_time))
				return err_is_not_uint(KeyServiceConfig::recover_time, service.service_name);
		}

		{
			if(!a.HasMember(KeyServiceConfig::depend_map.c_str()))
				return err_is_not_array(KeyServiceConfig::depend_map);
			const rapidjson::Value& cv = a[KeyServiceConfig::depend_map.c_str()];
			if(!cv.IsArray())
				return err_is_not_array(KeyServiceConfig::depend_map, service.service_name);

			const auto& brray = cv.GetArray();
			for(const auto& b : brray)
			{
				Depend depend;
				if(!get_uint(b, KeyServiceConfig::depend_service_id, depend.depend_service_id))
					return err_is_not_uint(KeyServiceConfig::depend_service_id, service.service_name);

				service.depend_map.insert(std::make_pair(depend.depend_service_id, depend));
			}

			if(service.depend_map.size() != brray.Size())
				return err_is_not_unique(KeyServiceConfig::depend_service_id, service.service_name);
		}

		{
			if(!a.HasMember(KeyServiceConfig::kv_map.c_str()))
				return err_is_not_array(KeyServiceConfig::kv_map);
			const rapidjson::Value& cv = a[KeyServiceConfig::kv_map.c_str()];
			if(!cv.IsArray())
				return err_is_not_array(KeyServiceConfig::kv_map, service.service_name);

			const auto& brray = cv.GetArray();
			for(const auto& b : brray)
			{
				KV kv;
				if(!get_string(b, KeyServiceConfig::key, kv.key))
					return err_is_not_string(KeyServiceConfig::key, service.service_name);
				if(!get_string(b, KeyServiceConfig::val, kv.val))
					return err_is_not_string(KeyServiceConfig::val, service.service_name);

				service.kv_map.insert(std::make_pair(kv.key, kv));
			}

			if(service.kv_map.size() != brray.Size())
				return err_is_not_unique(KeyServiceConfig::key, service.service_name);
		}


		{
			std::set<unsigned int> check_proc_id;
			{
				if(!a.HasMember(KeyServiceConfig::heartbeat_list.c_str()))
					return err_is_not_array(KeyServiceConfig::heartbeat_list);
				const rapidjson::Value& cv = a[KeyServiceConfig::heartbeat_list.c_str()];
				if(!cv.IsArray())
					return err_is_not_array(KeyServiceConfig::heartbeat_list, service.service_name);

				const auto& brray = cv.GetArray();
				for(const auto& b : brray)
				{
					IPInfo ip_info;
					if(!get_uint(b, KeyServiceConfig::proc_id, ip_info.proc_id))
						return err_is_not_uint(KeyServiceConfig::proc_id, service.service_name);
					if(!get_string(b, KeyServiceConfig::proc_des, ip_info.proc_des))
						return err_is_not_string(KeyServiceConfig::proc_des, service.service_name);
					if(!get_string(b, KeyServiceConfig::in_ip, ip_info.in_ip))
						return err_is_not_string(KeyServiceConfig::in_ip, service.service_name);
					if(!get_uint(b, KeyServiceConfig::in_port, ip_info.in_port))
						return err_is_not_uint(KeyServiceConfig::in_port, service.service_name);
					if(!get_string(b, KeyServiceConfig::out_ip, ip_info.out_ip))
						return err_is_not_string(KeyServiceConfig::out_ip, service.service_name);
					if(!get_uint(b, KeyServiceConfig::out_port, ip_info.out_port))
						return err_is_not_uint(KeyServiceConfig::out_port, service.service_name);

					ip_info.change();
					service.heartbeat_list.push_back(ip_info);
					check_proc_id.insert(ip_info.proc_id);
				}
			}

			{
				if(!a.HasMember(KeyServiceConfig::inservice_list.c_str()))
					return err_is_not_array(KeyServiceConfig::inservice_list);
				const rapidjson::Value& cv = a[KeyServiceConfig::inservice_list.c_str()];
				if(!cv.IsArray())
					return err_is_not_array(KeyServiceConfig::inservice_list, service.service_name);

				const auto& brray = cv.GetArray();
				for(const auto& b : brray)
				{
					IPInfo ip_info;
					if(!get_uint(b, KeyServiceConfig::proc_id, ip_info.proc_id))
						return err_is_not_uint(KeyServiceConfig::proc_id, service.service_name);
					if(!get_string(b, KeyServiceConfig::proc_des, ip_info.proc_des))
						return err_is_not_string(KeyServiceConfig::proc_des, service.service_name);
					if(!get_string(b, KeyServiceConfig::in_ip, ip_info.in_ip))
						return err_is_not_string(KeyServiceConfig::in_ip, service.service_name);
					if(!get_uint(b, KeyServiceConfig::in_port, ip_info.in_port))
						return err_is_not_uint(KeyServiceConfig::in_port, service.service_name);
					if(!get_string(b, KeyServiceConfig::out_ip, ip_info.out_ip))
						return err_is_not_string(KeyServiceConfig::out_ip, service.service_name);
					if(!get_uint(b, KeyServiceConfig::out_port, ip_info.out_port))
						return err_is_not_uint(KeyServiceConfig::out_port, service.service_name);

					ip_info.change();
					service.inservice_list.push_back(ip_info);
					check_proc_id.insert(ip_info.proc_id);
				}
			}

			if(check_proc_id.size() != service.heartbeat_list.size() + service.inservice_list.size())
				return err_is_not_unique(KeyServiceConfig::proc_id, service.service_name);
		}

		_service_map.insert(std::make_pair(service.service_id, service));
	}

	if(_service_map.size() != array.Size())
		return err_is_not_unique(KeyServiceConfig::service_id);
	if(check_service_name.size() != array.Size())
		return err_is_not_unique(KeyServiceConfig::service_name);

	for(auto& it_service : _service_map)
	{
		Service& service = it_service.second;
		for(auto& it_depend : service.depend_map)
		{
			Depend& depend = it_depend.second;
			auto it = _service_map.find(depend.depend_service_id);
			if(it == _service_map.end())
			{
				return err_depend_service_id_is_not_exist(depend.depend_service_id);
			}
		}
	}

	return "";
}

std::string ServiceConfig::map_to_json()
{
	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
	
	writer.StartObject();
	{
		writer.Key(KeyServiceConfig::service_map.c_str());
		writer.StartArray();
		{
			for(auto& it_service : _service_map)
			{
				writer.StartObject();
				{
					Service& service = it_service.second;
					writer.Key(KeyServiceConfig::service_id.c_str());
					writer.Uint(service.service_id);
					writer.Key(KeyServiceConfig::service_name.c_str());
					writer.String(service.service_name.c_str());
					
					writer.Key(KeyServiceConfig::heartbeat.c_str());
					writer.StartObject();
					{
						writer.Key(KeyServiceConfig::heartbeat_enable.c_str());
						writer.Bool(service.heartbeat.heartbeat_enable);
						writer.Key(KeyServiceConfig::heartbeat_gap.c_str());
						writer.Uint(service.heartbeat.heartbeat_gap);
						writer.Key(KeyServiceConfig::lose_time.c_str());
						writer.Uint(service.heartbeat.lose_time);
						writer.Key(KeyServiceConfig::recover_time.c_str());
						writer.Uint(service.heartbeat.recover_time);
					}	
					writer.EndObject();

					writer.Key(KeyServiceConfig::depend_map.c_str());
					writer.StartArray();
					{
						for(auto& it_kv : service.depend_map)
						{
							writer.StartObject();
							{
								Depend& depend = it_kv.second;
								writer.Key(KeyServiceConfig::depend_service_id.c_str());
								writer.Uint(depend.depend_service_id);
							}
							writer.EndObject();
						}
					}
					writer.EndArray();

					writer.Key(KeyServiceConfig::kv_map.c_str());
					writer.StartArray();
					{
						for(auto& it_kv : service.kv_map)
						{
							writer.StartObject();
							{
								KV& kv = it_kv.second;
								writer.Key(KeyServiceConfig::key.c_str());
								writer.String(kv.key.c_str());
								writer.Key(KeyServiceConfig::val.c_str());
								writer.String(kv.val.c_str());
							}
							writer.EndObject();
						}
					}
					writer.EndArray();

					writer.Key(KeyServiceConfig::heartbeat_list.c_str());
					writer.StartArray();
					{
						for(auto& ip_info : service.heartbeat_list)
						{
							writer.StartObject();
							{
								writer.Key(KeyServiceConfig::proc_id.c_str());
								writer.Uint(ip_info.proc_id);
								writer.Key(KeyServiceConfig::proc_des.c_str());
								writer.String(ip_info.proc_des.c_str());
								writer.Key(KeyServiceConfig::in_ip.c_str());
								writer.String(ip_info.in_ip.c_str());
								writer.Key(KeyServiceConfig::in_port.c_str());
								writer.Uint(ip_info.in_port);
								writer.Key(KeyServiceConfig::out_ip.c_str());
								writer.String(ip_info.out_ip.c_str());
								writer.Key(KeyServiceConfig::out_port.c_str());
								writer.Uint(ip_info.out_port);
							}
							writer.EndObject();
						}
					}
					writer.EndArray();

					writer.Key(KeyServiceConfig::inservice_list.c_str());
					writer.StartArray();
					{
						for(auto& ip_info : service.inservice_list)
						{
							writer.StartObject();
							{
								writer.Key(KeyServiceConfig::proc_id.c_str());
								writer.Uint(ip_info.proc_id);
								writer.Key(KeyServiceConfig::proc_des.c_str());
								writer.String(ip_info.proc_des.c_str());
								writer.Key(KeyServiceConfig::in_ip.c_str());
								writer.String(ip_info.in_ip.c_str());
								writer.Key(KeyServiceConfig::in_port.c_str());
								writer.Uint(ip_info.in_port);
								writer.Key(KeyServiceConfig::out_ip.c_str());
								writer.String(ip_info.out_ip.c_str());
								writer.Key(KeyServiceConfig::out_port.c_str());
								writer.Uint(ip_info.out_port);
							}
							writer.EndObject();
						}
					}
					writer.EndArray();
					
				}
				writer.EndObject();
			}
		}	
		writer.EndArray();
	}
	writer.EndObject();

	return sb.GetString();
}

bool ServiceConfig::get_string(const rapidjson::Value& v, const std::string& key, std::string& str)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsString())
		{
			str = tmp.GetString();
			return str.size() > 0;
		}
	}

	return false;
}

bool ServiceConfig::get_uint(const rapidjson::Value& v, const std::string& key, unsigned short& i)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsUint())
		{
			i = tmp.GetUint();
			return i != 0;
		}
	}

	return false;
}

bool ServiceConfig::get_uint(const rapidjson::Value& v, const std::string& key, unsigned int& i)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsUint())
		{
			i = tmp.GetUint();
			return i != 0;
		}
	}

	return false;
}

bool ServiceConfig::get_bool(const rapidjson::Value& v, const std::string& key, bool& b)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsBool())
		{
			b = tmp.GetBool();
			return true;
		}
	}

	return false;
}

ServiceConfig::Service* ServiceConfig::get_service(unsigned short service_id)
{
	if(service_id != 0)
	{
		auto it = _service_map.find(service_id);
		if(it != _service_map.end())
		{
			return &it->second;
		}
	}

	return nullptr;
}

std::string ServiceConfig::get_service_list()
{
	 ServiceConfig sc = copy();
	 for(auto& it_service : sc._service_map)
	 {
		 Service& service = it_service.second;
		 service.depend_map.clear();
		 service.kv_map.clear();
		 service.heartbeat_list.clear();
		 service.inservice_list.clear();
	 }
	
	 return sc.map_to_json();
}

bool ServiceConfig::get_service_info(unsigned short service_id, std::string& json)
{
	auto p = get_service(service_id);
	if(p !=nullptr)
	{
		ServiceConfig sc;
		sc._service_map.insert(std::make_pair(p->service_id, *p));
		json = sc.map_to_json();
		return true;
	}

	return false;
}

bool ServiceConfig::get_service_conf(unsigned short service_id, std::string& json)
{
	auto p = get_service(service_id);
	if(p !=nullptr)
	{
		ServiceConfig sc;

		Service service_self = *p;
		service_self.heartbeat_list.clear();
		service_self.inservice_list.clear();

		for(auto it = p->depend_map.begin();  it != p->depend_map.end(); it++)
		{
			auto p_depend_service = get_service(it->second.depend_service_id);
			if(p_depend_service == nullptr)
			{
				return false;
			}
			
			if(p_depend_service->service_id == service_id)
			{
				// 服务依赖自己的服务,加入正常服务的ip_info
				for(unsigned int i = 0; i != p_depend_service->inservice_list.size(); i++)
				{
					const ServiceConfig::IPInfo& ip_info = p_depend_service->inservice_list[i];
					if(ip_info._ip_info_derivative.is_run)
					{
						service_self.inservice_list.push_back(ip_info);
					}
				}
			}
			else
			{
				// 依赖别的服务,加入正常服务的ip_info
				Service service;
				service.service_id = p_depend_service->service_id;
				service.service_name = p_depend_service->service_name;
				for(unsigned int i = 0; i != p_depend_service->inservice_list.size(); i++)
				{
					const ServiceConfig::IPInfo& ip_info = p_depend_service->inservice_list[i];
					if(ip_info._ip_info_derivative.is_run)
					{
						service.inservice_list.push_back(ip_info);
					}
				}
				sc._service_map.insert(std::make_pair(service.service_id, service));
			}
		}

		sc._service_map.insert(std::make_pair(service_self.service_id, service_self));
		json = sc.map_to_json();
		return true;
	}

	return false;
}

bool ServiceConfig::set_service_heartbeat(unsigned short service_id, const Heartbeat& heartbeat)
{
	if(heartbeat.heartbeat_gap != 0 && heartbeat.lose_time != 0 && heartbeat.recover_time != 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			p->heartbeat = heartbeat;

			// 触发center同步
			_config_derivative.sync_config();
			return true;
		}
	}

	return false;
}

bool ServiceConfig::add_service_depend(unsigned short service_id, unsigned short depend_service_id)
{
	if(depend_service_id != 0)
	{
		auto p = get_service(service_id);
		auto p_depend_service_id = get_service(depend_service_id);
		if(p != nullptr && p_depend_service_id != nullptr && p_depend_service_id->inservice_list.size() > 0)
		{
			// 依赖服务的inservice_list必须有可服务的机器才能加入依赖
			auto it = p->depend_map.find(depend_service_id);
			if(it == p->depend_map.end())
			{
				Depend depend;
				depend.depend_service_id = depend_service_id;
				p->depend_map.insert(std::make_pair(depend.depend_service_id, depend));

				// 触发serivce配置同步，触发center配置同步
				_config_derivative.sync_config(p->_service_derivative.sync_service());
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::del_service_depend(unsigned short service_id, unsigned short depend_service_id)
{
	if(depend_service_id != 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			auto it = p->depend_map.find(depend_service_id);
			if(it != p->depend_map.end())
			{
				p->depend_map.erase(it);

				// 触发serivce配置同步，触发center配置同步
				_config_derivative.sync_config(p->_service_derivative.sync_service());
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::set_service_kv(unsigned short service_id, const KV& kv)
{
	if(kv.key.size() > 0 && kv.val.size() > 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			auto it = p->kv_map.find(kv.key);
			if(it != p->kv_map.end())
			{
				it->second = kv;

				// 触发serivce配置同步，触发center配置同步
				_config_derivative.sync_config(p->_service_derivative.sync_service());
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::add_service_kv(unsigned short service_id, const KV& kv)
{
	if(kv.key.size() > 0 && kv.val.size() > 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			auto it = p->kv_map.find(kv.key);
			if(it == p->kv_map.end())
			{
				p->kv_map.insert(std::make_pair(kv.key, kv));

				// 触发serivce配置同步，触发center配置同步
				_config_derivative.sync_config(p->_service_derivative.sync_service());
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::del_service_kv(unsigned short service_id, const std::string& key)
{
	if(key.size() > 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			auto it = p->kv_map.find(key);
			if(it != p->kv_map.end())
			{
				p->kv_map.erase(key);

				// 触发serivce配置同步，触发center配置同步
				_config_derivative.sync_config(p->_service_derivative.sync_service());
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::add_service_heartbeat_list(unsigned short service_id, const IPInfo& ip_info)
{
	if(ip_info.proc_id != 0 && ip_info.proc_des.size() > 0 && ip_info.in_ip.size() > 0 && ip_info.in_port != 0 && ip_info.out_ip.size() > 0 && ip_info.out_port != 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			auto it_heartbeat_list = std::find(p->heartbeat_list.begin(), p->heartbeat_list.end(), ip_info.proc_id);
			auto it_inservice_list = std::find(p->inservice_list.begin(), p->inservice_list.end(), ip_info.proc_id);
			if(it_heartbeat_list == p->heartbeat_list.end() && it_inservice_list == p->inservice_list.end())
			{
				p->heartbeat_list.push_back(ip_info);

				// 只触发config配置同步，service配置不需要同步
				_config_derivative.sync_config(ip_info._ip_info_derivative.update_time);
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::del_service_heartbeat_list(unsigned short service_id, unsigned int proc_id)
{
	if(proc_id != 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			auto it = std::find(p->heartbeat_list.begin(), p->heartbeat_list.end(), proc_id);
			if(it != p->heartbeat_list.end())
			{
				p->heartbeat_list.erase(it);

				// 只触发config配置同步，service配置不需要同步
				_config_derivative.sync_config();
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::add_service_inservice_list(unsigned short service_id, unsigned int proc_id)
{
	if(proc_id != 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			auto it_heartbeat_list = std::find(p->heartbeat_list.begin(), p->heartbeat_list.end(), proc_id);
			auto it_inservice_list = std::find(p->inservice_list.begin(), p->inservice_list.end(), proc_id);
			if(it_heartbeat_list != p->heartbeat_list.end() && it_inservice_list ==  p->inservice_list.end())
			{
				IPInfo ip_info = *it_heartbeat_list;

				// 触发serivce配置同步，触发center配置同步
				_config_derivative.sync_config(p->_service_derivative.sync_service(
					ip_info._ip_info_derivative.update_time_now()));

				p->heartbeat_list.erase(it_heartbeat_list);
				p->inservice_list.push_back(ip_info);
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::del_service_inservice_list(unsigned short service_id, unsigned int proc_id)
{
	if(proc_id != 0)
	{
		auto p = get_service(service_id);
		if(p != nullptr)
		{
			auto it_heartbeat_list = std::find(p->heartbeat_list.begin(), p->heartbeat_list.end(), proc_id);
			auto it_inservice_list = std::find(p->inservice_list.begin(), p->inservice_list.end(), proc_id);
			if(it_heartbeat_list == p->heartbeat_list.end() && it_inservice_list !=  p->inservice_list.end())
			{
				IPInfo ip_info = *it_inservice_list;

				// 触发serivce配置同步，触发center配置同步
				_config_derivative.sync_config(p->_service_derivative.sync_service(
					ip_info._ip_info_derivative.update_time_now()));

				p->inservice_list.erase(it_inservice_list);
				p->heartbeat_list.push_back(ip_info);
				return true;
			}
		}
	}

	return false;
}

bool ServiceConfig::add_service(unsigned short service_id, const std::string& service_name, const Heartbeat& heartbeat)
{
	if(service_id != 0 && service_name.size() > 0 && heartbeat.heartbeat_gap != 0 && heartbeat.lose_time != 0 && heartbeat.recover_time != 0)
	{
		for(auto& it_service : _service_map)
		{
			if(it_service.second.service_id == service_id || it_service.second.service_name == service_name)
			{
				return false;
			}
		}

		Service service;
		service.service_id = service_id;
		service.service_name = service_name;	
		service.heartbeat = heartbeat;
		_service_map.insert(std::make_pair(service.service_id, service));

		// 触发config配置同步
		_config_derivative.sync_config(service._service_derivative.update_time);
		return true;
	}

	return false;
}

bool ServiceConfig::del_service(unsigned short service_id)
{
	if(service_id != 0)
	{
		auto it = _service_map.find(service_id);
		if(it != _service_map.end())
		{
			// 删除service要检查是否有其他service的依赖,除自己依赖自己以外
			for(auto it_service = _service_map.begin(); it_service != _service_map.end(); it++)
			{
				if(it_service->second.service_id != service_id)
				{
					auto it_find = it_service->second.depend_map.find(service_id);
					if(it_find != it_service->second.depend_map.end())
					{
						return false;	// 还有其他服务在依赖该service
					}
				}
			}

			// 删除service没有其他service的依赖，可以删除依赖
			_service_map.erase(it);

			// 触发config配置同步
			_config_derivative.sync_config();
			return true;
		}
	}

	return false;
}

void ServiceConfig::IPInfo::change()
{
	ip = Util::sip_2_uip(in_ip.c_str());
	key_in_ip_port = Util::uiui2ull(ip, in_port);
}


