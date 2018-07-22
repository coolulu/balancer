#include "BHttpServer.h"

#include <boost/bind.hpp>
#include "Proc.h"
#include "log/Log.h"
#include "tool/Util.h"

BHttpServer::BHttpServer(Proc& proc) : _proc(proc), _p_http_server(nullptr)
{
	_map_http_req.insert(std::make_pair("/info", &BHttpServer::info));
	_map_http_req.insert(std::make_pair("/count", &BHttpServer::count));
	_map_http_req.insert(std::make_pair("/stop", &BHttpServer::stop));
	_map_http_req.insert(std::make_pair("/reload", &BHttpServer::reload));

	_map_http_req.insert(std::make_pair("/get_service_list", &BHttpServer::get_service_list));
	_map_http_req.insert(std::make_pair("/get_service_info", &BHttpServer::get_service_info));

	_map_http_req.insert(std::make_pair("/set_service_heartbeat", &BHttpServer::set_service_heartbeat));
	_map_http_req.insert(std::make_pair("/add_service_depend", &BHttpServer::add_service_depend));
	_map_http_req.insert(std::make_pair("/del_service_depend", &BHttpServer::del_service_depend));
	_map_http_req.insert(std::make_pair("/set_service_kv", &BHttpServer::set_service_kv));
	_map_http_req.insert(std::make_pair("/add_service_kv", &BHttpServer::add_service_kv));
	_map_http_req.insert(std::make_pair("/del_service_kv", &BHttpServer::del_service_kv));
	_map_http_req.insert(std::make_pair("/add_service_heartbeat_list", &BHttpServer::add_service_heartbeat_list));
	_map_http_req.insert(std::make_pair("/del_service_heartbeat_list", &BHttpServer::del_service_heartbeat_list));
	_map_http_req.insert(std::make_pair("/add_service_inservice_list", &BHttpServer::add_service_inservice_list));
	_map_http_req.insert(std::make_pair("/del_service_inservice_list", &BHttpServer::del_service_inservice_list));
	_map_http_req.insert(std::make_pair("/add_service", &BHttpServer::add_service));
	_map_http_req.insert(std::make_pair("/del_service", &BHttpServer::del_service));
}

BHttpServer::~BHttpServer()
{
	if(_p_http_server == nullptr)
	{
		delete _p_http_server;
		_p_http_server = nullptr;
	}
}

void BHttpServer::start()
{
	if(_p_http_server == nullptr)
	{
		_p_http_server = new muduo::net::HttpServer(&_proc._loop, 
			muduo::net::InetAddress(_proc._config.net.http.ip, _proc._config.net.http.port), "HttpServer");
		_p_http_server->setHttpCallback(boost::bind(&BHttpServer::on_http_request, this, _1, _2));
		_p_http_server->start();
	}
}

void BHttpServer::on_http_request(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	B_LOG_INFO << "method=" << req.methodString() << ", path=" << req.path() << ", query=" << req.query() << ", receiveTime=" << req.receiveTime().toString();

	auto it = _map_http_req.find(req.path().c_str());
	if(it != _map_http_req.end())
	{
		return (this->*(it->second))(req, rsp);
	}

	return unknow(req, rsp);
}

void BHttpServer::unknow(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	rsp->setStatusCode(muduo::net::HttpResponse::k404NotFound);
	rsp->setStatusMessage("Not Found");
	rsp->setBody("{}");
	rsp->setCloseConnection(true);
}

void BHttpServer::info(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	send_http_rsp(rsp, "{\"a\": 1, \"b\": 2}");
}

void BHttpServer::count(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{

}

void BHttpServer::stop(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{

}

void BHttpServer::reload(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{

}

void BHttpServer::get_service_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	send_http_rsp(rsp, _proc._sc.get_service_list());
}

void BHttpServer::get_service_info(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	std::string json = "{}";

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id);
	if(b)
	{
		b = _proc._sc.get_service_info(service_id, json);
	}

	send_http_rsp(rsp, json);
}

void BHttpServer::set_service_heartbeat(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	ServiceConfig::Heartbeat heartbeat;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id)	&&
			 get_key_val(req.query().c_str(), KeyServiceConfig::heartbeat_enable, heartbeat.heartbeat_enable) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::heartbeat_gap, heartbeat.heartbeat_gap) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::lose_time, heartbeat.lose_time) && 
			 get_key_val(req.query().c_str(), KeyServiceConfig::recover_time, heartbeat.recover_time);
	if(b)
	{
		b = _proc._sc.set_service_heartbeat(service_id, heartbeat);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::add_service_depend(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	unsigned short depend_service_id = 0;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::depend_service_id, depend_service_id);
	if(b)
	{
		b = _proc._sc.add_service_depend(service_id, depend_service_id);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::del_service_depend(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	unsigned short depend_service_id = 0;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::depend_service_id, depend_service_id);
	if(b)
	{
		b = _proc._sc.del_service_depend(service_id, depend_service_id);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::set_service_kv(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	ServiceConfig::KV kv;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::key, kv.key) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::val, kv.val);
	if(b)
	{
		b = _proc._sc.set_service_kv(service_id, kv);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::add_service_kv(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	ServiceConfig::KV kv;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::key, kv.key) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::val, kv.val);
	if(b)
	{
		b = _proc._sc.add_service_kv(service_id, kv);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::del_service_kv(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	std::string key;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::key, key);
	if(b)
	{
		b = _proc._sc.del_service_kv(service_id, key);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::add_service_heartbeat_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	ServiceConfig::IPInfo ip_info;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::proc_id, ip_info.proc_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::proc_des, ip_info.proc_des) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::in_ip, ip_info.in_ip) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::out_ip, ip_info.out_ip) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::port, ip_info.port);
	if(b)
	{
		b = _proc._sc.add_service_heartbeat_list(service_id, ip_info);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::del_service_heartbeat_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	unsigned int proc_id = 0;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::proc_id, proc_id);
	if(b)
	{
		b = _proc._sc.del_service_heartbeat_list(service_id, proc_id);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::add_service_inservice_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	unsigned int proc_id = 0;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::proc_id, proc_id);
	if(b)
	{
		b = _proc._sc.add_service_inservice_list(service_id, proc_id);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::del_service_inservice_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;
	unsigned int proc_id = 0;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::proc_id, proc_id);
	if(b)
	{
		b = _proc._sc.del_service_inservice_list(service_id, proc_id);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::add_service(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id;
	std::string service_name;
	ServiceConfig::Heartbeat heartbeat;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::service_name, service_name) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::heartbeat_enable, heartbeat.heartbeat_enable) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::heartbeat_gap, heartbeat.heartbeat_gap) &&
			 get_key_val(req.query().c_str(), KeyServiceConfig::lose_time, heartbeat.lose_time) && 
			 get_key_val(req.query().c_str(), KeyServiceConfig::recover_time, heartbeat.recover_time);
	if(b)
	{
		b = _proc._sc.add_service(service_id, service_name, heartbeat);
	}

	send_http_rsp(rsp, b);
}

void BHttpServer::del_service(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	unsigned short service_id = 0;

	bool b = get_key_val(req.query().c_str(), KeyServiceConfig::service_id, service_id);
	if(b)
	{
		b = _proc._sc.del_service(service_id);
	}

	send_http_rsp(rsp, b);
}

bool BHttpServer::get_key_val(const std::string& query, const std::string& key, unsigned int& i)
{
	std::string str;
	bool b = get_key_val(query, key, str);
	if(b)
	{
		i = Util::str_2_uint(str);
		return true;
	}

	return false;
}

bool BHttpServer::get_key_val(const std::string& query, const std::string& key, unsigned short& i)
{
	std::string str;
	bool b = get_key_val(query, key, str);
	if(b)
	{
		i = Util::str_2_ushort(str);
		return true;
	}

	return false;
}

bool BHttpServer::get_key_val(const std::string& query, const std::string& key, std::string& str)
{
	std::string key_new = key + '=';
	size_t begin = query.find(key_new);
	if(begin != std::string::npos)
	{
		size_t end = query.find('&', begin + key_new.size());
		if(end != std::string::npos)
		{
			str = query.substr(begin + key_new.size(), end - begin - key_new.size());
			if(str.size() > 0)
			{
				return true;
			}		
		}
	}

	return false;
}

bool BHttpServer::get_key_val(const std::string& query, const std::string& key, bool& b)
{
	std::string str;
	bool tmp = get_key_val(query, key, str);
	if(tmp)
	{
		if(str == "0")
		{
			b = false;
			return true;
		}

		if(str == "1")
		{
			b = true;
			return true;
		}
	}

	return false;
}

void BHttpServer::send_http_rsp(muduo::net::HttpResponse* rsp, bool b)
{
	rsp->setStatusCode(muduo::net::HttpResponse::k200Ok);
	rsp->setStatusMessage("OK");
	if(b)
	{
		rsp->setBody("{\"code\": 0}");
	}
	else
	{
		rsp->setBody("{\"code\": -1}");
	}
	rsp->setCloseConnection(true);
}

void BHttpServer::send_http_rsp(muduo::net::HttpResponse* rsp, const std::string& body)
{
	rsp->setStatusCode(muduo::net::HttpResponse::k200Ok);
	rsp->setStatusMessage("OK");
	rsp->setBody(body.c_str());
	rsp->setCloseConnection(true);
}












