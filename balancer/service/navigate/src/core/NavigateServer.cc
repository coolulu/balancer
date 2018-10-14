#include "NavigateServer.h"

#include <sstream>
#include <iomanip>

#include <boost/bind.hpp>
#include "Proc.h"
#include "log/Log.h"
#include "tool/Util.h"
#include "protocol/Protocol.h"

NavigateServer::NavigateServer(Proc& proc, unsigned int index, muduo::net::EventLoop* loop)
	:	_proc(proc), 
		_index(index), 
		_http_server(loop, 
					 muduo::net::InetAddress(_proc._config.net.navigate.ip, _proc._config.net.navigate.port),
					 "NavigateServer",
					 muduo::net::TcpServer::kReusePort)
{
	_http_server.setHttpCallback(boost::bind(&NavigateServer::on_http_request, this, _1, _2));
	_http_server.getLoop()->runInLoop(boost::bind(&muduo::net::HttpServer::start, &_http_server));
}

NavigateServer::~NavigateServer()
{

}

void NavigateServer::on_http_request(const muduo::net::HttpRequest& req, muduo::net::HttpResponse* rsp)
{
	B_LOG_INFO << "_index=" << _index;
	B_LOG_INFO << "method=" << req.methodString();
	B_LOG_INFO << "path=" << req.path();
	B_LOG_INFO << "query=" << req.query();
	B_LOG_INFO << "receiveTime=" << req.receiveTime().toString();

	if(req.path() == "/GetAccess")
	{
		rsp->setStatusCode(muduo::net::HttpResponse::k200Ok);
		rsp->setStatusMessage("OK");
		rsp->setCloseConnection(true);
		
		if(req.query().size() <= 1)
		{
			B_LOG_WARN << "req.query.size <= 1, req.query.size=" << req.query().size();
			return;
		}

		if(req.query()[0] != '?')
		{
			B_LOG_WARN << "req.query[0] is not '?', req.query[0]=" << req.query()[0];
			return;
		}

		std::string data(req.query().c_str() + 1, req.query().size() - 1);
		navigate::GetAccessReq getAccessReq;
		bool b = getAccessReq.ParseFromString(data);
		if(!b)
		{
			B_LOG_WARN << "ParseFromString=false, data=" << data;
			return;
		}

		unsigned short service_id = getAccessReq.service_id();
		unsigned long long user_id = getAccessReq.user_id();

		if(service_id == 0 || user_id == 0)
		{
			B_LOG_WARN	<< "service_id is 0 or user_id is 0"
						<< ", service_id=" << service_id
						<< ", user_id=" << user_id;
			return;
		}

		B_LOG_INFO	<< "GetAccessReq" << ", service_id=" << service_id << ", user_id=" << user_id;

		LoadProc load_proc;
		{
			muduo::MutexLockGuard mlg(_mutex_load_result);
			b = _load_result.find(service_id, load_proc);
		}

		if(!b)
		{
			B_LOG_WARN << "_load_result.find is false";
			return;	
		}

		// unsigned long long范围[0, 18446744073709551615], strlen("18446744073709551615") = 20
		// unsigned long long转字符串不足20位前面补0
		std::stringstream ss_user_id;
		ss_user_id << std::setfill('0') << std::setw(20) << user_id;
		std::string str_user_id = ss_user_id.str();

		unsigned long long now = Util::get_us();
		std::stringstream ss_now;
		ss_now << std::setfill('0') << std::setw(20) << now;
		std::string str_now = ss_now.str();

		if(str_user_id.size() != 20 || str_now.size() != 20)
		{
			B_LOG_ERROR << "str_user_id.size() != 20 or str_now.size() != 20"
						<< ", user_id=" << user_id
						<< ", str_user_id=" << str_user_id
						<< ", now=" << now
						<< ", str_now=" << str_now;
			return;
		}

		std::string navigate_key = "1";
		if(navigate_key.empty())
		{
			B_LOG_ERROR << "navigate_key is empty";
			return;
		}

		std::string user_key;
		user_key = str_user_id[18] + str_now[19] 
				 + str_user_id[16] + str_now[17] 
				 + str_user_id[14] + str_now[15] 
				 + str_user_id[12] + str_now[13] 
				 + str_user_id[10] + str_now[11] 
				 + str_user_id[8]  + str_now[9] 
				 + str_user_id[6]  + str_now[7] 
				 + str_user_id[4]  + str_now[5] 
				 + str_user_id[2]  + str_now[3] 
				 + str_user_id[0]  + str_now[1] 
				 + str_user_id[1]  + str_now[0]
				 + str_user_id[3]  + str_now[2]
				 + str_user_id[5]  + str_now[4]
				 + str_user_id[7]  + str_now[6]
				 + str_user_id[9]  + str_now[8]
				 + str_user_id[11] + str_now[10]
				 + str_user_id[13] + str_now[12]
				 + str_user_id[15] + str_now[14]
				 + str_user_id[17] + str_now[16]
				 + str_user_id[19] + str_now[18];

		std::string access_key;
		for(unsigned int i = 0; i != user_key.size(); i++)
		{
			access_key += user_key[i] ^ navigate_key[i % navigate_key.size()];
		}

		B_LOG_INFO	<< "navigate_key=" << navigate_key
					<< ", user_key=" << user_key
					<< ", access_key=" << access_key;

		navigate::GetAccessRsp getAccessRsp;
		getAccessRsp.set_access_key(access_key);
		getAccessRsp.set_service_id(load_proc._service_id);
		getAccessRsp.set_proc_id(load_proc._ip_info.proc_id);
		getAccessRsp.set_out_ip(load_proc._ip_info.out_ip);
		getAccessRsp.set_out_port(load_proc._ip_info.out_port);

		std::string body;
		b = getAccessRsp.SerializeToString(&body);
		if(b)
		{
			rsp->setBody(body.c_str());
		}
		else
		{
			B_LOG_WARN << "SerializeToString=false";
		}

		return;
	}
	else
	{
		rsp->setStatusCode(muduo::net::HttpResponse::k404NotFound);
		rsp->setStatusMessage("Not Found");
		rsp->setCloseConnection(true);
	}
}

void NavigateServer::ready_destroy()
{
	// 不能跨线程释放,唤醒所在的线程再释放
	_http_server.getLoop()->runInLoop(boost::bind(&NavigateServer::destroy, this));
}

void NavigateServer::destroy()
{
	delete this;
}

void NavigateServer::update_load_result(const LoadResult& load_result)
{
	{
		muduo::MutexLockGuard mlg(_mutex_load_result);
		_load_result = load_result;
	}

	B_LOG_INFO	<< "_index=" << _index
				<< ", _update_count=" << load_result._update_count
				<< ", _update_time=" << load_result._update_time;
}

NavigatePool::NavigatePool(Proc& proc)
	:	_proc(proc),
		_thread_size(::sysconf(_SC_NPROCESSORS_CONF))
{

}

NavigatePool::~NavigatePool()
{
	for(auto p_navigate_server :  _navigate_server_vector)
	{	
		p_navigate_server->ready_destroy();
		p_navigate_server = nullptr;
	}

	_navigate_server_vector.clear();

	if(_p_event_loop_thread_pool != nullptr)
	{
		delete _p_event_loop_thread_pool;
		_p_event_loop_thread_pool = nullptr;
	}
}

void NavigatePool::start()
{
	if(_p_event_loop_thread_pool == nullptr)
	{
		_p_event_loop_thread_pool = new muduo::net::EventLoopThreadPool(&_proc._loop, "NavigatePool");
		_p_event_loop_thread_pool->setThreadNum(_thread_size);
		_p_event_loop_thread_pool->start();
	}

	for(int i = 0; i != _thread_size; i++)
	{
		_navigate_server_vector.push_back(new NavigateServer(_proc, i, _p_event_loop_thread_pool->getNextLoop()));
	}
}

