#pragma once

#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>

class Proc;

class BHttpServer
{
public:
	BHttpServer(Proc& proc);
	~BHttpServer();

public:
	void start();

private:
	void on_http_request(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);

	// base
	void unknow(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void info(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void count(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void stop(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void reload(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);

	// read
	void get_service_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void get_service_info(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void get_service_conf(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);

	// write
	void set_service_heartbeat(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void add_service_depend(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void del_service_depend(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void set_service_kv(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void add_service_kv(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void del_service_kv(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void add_service_heartbeat_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void del_service_heartbeat_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void add_service_inservice_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void del_service_inservice_list(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void add_service(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	void del_service(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);

private:
	// ∏Ò Ω a=123&b=abc&c=0&
	bool get_key_val(const std::string& query, const std::string& key, unsigned int& i);
	bool get_key_val(const std::string& query, const std::string& key, unsigned short& i);
	bool get_key_val(const std::string& query, const std::string& key, std::string& str);
	bool get_key_val(const std::string& query, const std::string& key, bool& b);

private:
	void send_http_rsp(muduo::net::HttpResponse* rsp, bool b);
	void send_http_rsp(muduo::net::HttpResponse* rsp, const std::string& body);
	void save(bool b);
	
private:
	Proc& _proc;
	muduo::net::HttpServer* _p_http_server;

	typedef void (BHttpServer::*pFunHttpReq)(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp);
	std::map<std::string, pFunHttpReq> _map_http_req;
};