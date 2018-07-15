#pragma once

#include <string>
#include <vector>
#include <map>
#include <rapidjson/document.h>

namespace KeyServiceConfig
{
	static const std::string& service_map			= "service_map";
	static const std::string& service_id			= "service_id";
	static const std::string& service_name			= "service_name";

	static const std::string& heartbeat				= "heartbeat";
	static const std::string& heartbeat_enable		= "heartbeat_enable";
	static const std::string& heartbeat_gap			= "heartbeat_gap";
	static const std::string& lose_time				= "lose_time";
	static const std::string& recover_time			= "recover_time";

	static const std::string& depend_map			= "depend_map";
	static const std::string& depend_service_id		= "depend_service_id";

	static const std::string& kv_map				= "kv_map";
	static const std::string& key					= "key";
	static const std::string& val					= "val";

	static const std::string& heartbeat_list		= "heartbeat_list";
	static const std::string& inservice_list		= "inservice_list";
	static const std::string& proc_id				= "proc_id";
	static const std::string& proc_des				= "proc_des";
	static const std::string& in_ip					= "in_ip";
	static const std::string& out_ip				= "out_ip";
	static const std::string& port					= "port";
	
}

class ServiceConfig
{
public:
	struct Heartbeat
	{
		Heartbeat() : heartbeat_enable(false), heartbeat_gap(0), lose_time(0), recover_time(0){}

		bool			heartbeat_enable;
		unsigned short	heartbeat_gap;
		unsigned short	lose_time;
		unsigned short	recover_time;
	};

	struct Depend
	{
		unsigned short	depend_service_id;
	};

	struct KV
	{
		std::string	key;
		std::string	val;
	};

	struct IPInfo
	{
		IPInfo() : proc_id(0), port(0), ip(0), key_ip_port(0){}
		inline bool operator== (unsigned int proc_id) {return this->proc_id == proc_id;}
		void change();	//赋值ip,key_ip_port

		unsigned int		proc_id;
		std::string			proc_des;
		std::string			in_ip;
		std::string			out_ip;
		unsigned short		port;

		//不是配置文件里的变量
		unsigned int		ip;					// in_ip转换过来
		unsigned long long	key_ip_port;		// ip和port的组合key
	};

	struct Service
	{
		Service() : service_id(0){}

		unsigned short						service_id;
		std::string							service_name;
		Heartbeat							heartbeat;
		std::map<unsigned short, Depend>	depend_map;
		std::map<std::string, KV>			kv_map;
		std::vector<IPInfo>					heartbeat_list;
		std::vector<IPInfo>					inservice_list;
	};

public:
	ServiceConfig(){};

public:
	inline ServiceConfig copy(){return *this;}
	inline void assign(const ServiceConfig& sc){*this = sc;}
	inline std::map<unsigned short, Service>& get_service_map(){return _service_map;}

	std::string json_to_map(const std::string& json);
	std::string map_to_json();

public:		
	// read
	ServiceConfig::Service* get_service(unsigned short service_id);

	// 查询，返回service_id，service_name列表
	std::string get_service_list();	

	// 根据service_id查询，返回service_id，service_name，heartbeat，depend_map，kv_map，heartbeat_list，inservice_list
	bool get_service_info(unsigned short service_id, std::string& json);	

public:
	// write
	// 根据service_id，修改heartbeat成员值
	bool set_service_heartbeat(unsigned short service_id, const Heartbeat& heartbeat);

	// 根据service_id，depend_service_id，增加depend_map的depend_service_id
	bool add_service_depend(unsigned short service_id, unsigned short depend_service_id);

	// 根据service_id，depend_service_id，删除depend_map的depend_service_id
	bool del_service_depend(unsigned short service_id, unsigned short epend_service_id);

	// 根据service_id，key，value，修改kv_map的key对应val
	bool set_service_kv(unsigned short service_id, const KV& kv);

	// 根据service_id，key，value，增加kv_map的key，val
	bool add_service_kv(unsigned short service_id, const KV& kv);

	// 根据service_id，key，删除kv_map的key，val
	bool del_service_kv(unsigned short service_id, const std::string& key);

	// 根据service_id，proc_id，增加ip到heartbeat_list（上架）
	bool add_service_heartbeat_list(unsigned short service_id, const IPInfo& ip_info);

	// 根据service_id，proc_id，从heartbeat_list中删除proc_id（下架）
	bool del_service_heartbeat_list(unsigned short service_id, unsigned int proc_id);

	// 根据service_id，proc_id，从heartbeat_list的proc_id删除，增加到inservice_list（上线）
	bool add_service_inservice_list(unsigned short service_id, unsigned int proc_id);

	// 根据service_id，proc_id，从inservice_list的proc_id删除，增加到heartbeat_list（下线）
	bool del_service_inservice_list(unsigned short service_id, unsigned int proc_id);

	// 根据service_id，service_id，heartbeat增加service
	bool add_service(unsigned short service_id, const std::string& service_name, const Heartbeat& heartbeat);

	// 根据service_id，删除service
	bool del_service(unsigned short service_id);

private:
	bool get_string(const rapidjson::Value& v, const std::string& key, std::string& str);
	bool get_uint(const rapidjson::Value& v, const std::string& key, unsigned short& i);
	bool get_uint(const rapidjson::Value& v, const std::string& key, unsigned int& i);
	bool get_bool(const rapidjson::Value& v, const std::string& key, bool& b);

	inline std::string err_is_not_array(const std::string& key, const std::string& service_name = "")	{return key + " is not array " + (service_name.empty() ? "" : KeyServiceConfig::service_name + ": "+ service_name);}
	inline std::string err_is_not_object(const std::string& key, const std::string& service_name = "")	{return key + " is not object " + (service_name.empty() ? "" : KeyServiceConfig::service_name + ": "+ service_name);}
	inline std::string err_is_not_string(const std::string& key, const std::string& service_name = "")	{return key + " is not string " + (service_name.empty() ? "" : KeyServiceConfig::service_name + ": "+ service_name);}
	inline std::string err_is_not_uint(const std::string& key, const std::string& service_name = "")	{return key + " is not uint " + (service_name.empty() ? "" : KeyServiceConfig::service_name + ": "+ service_name);}
	inline std::string err_is_not_bool(const std::string& key, const std::string& service_name = "")	{return key + " is not bool " + (service_name.empty() ? "" : KeyServiceConfig::service_name + ": "+ service_name);}
	inline std::string err_is_not_unique(const std::string& key, const std::string& service_name = "")	{return key + " is not unique " + (service_name.empty() ? "" : KeyServiceConfig::service_name + ": "+ service_name);}
	inline std::string err_depend_service_id_is_not_exist(unsigned short depend_service_id)		{return KeyServiceConfig::depend_service_id + ": " + std::to_string(depend_service_id) + " is not exist";}

private:
	std::map<unsigned short, Service> _service_map;

};

