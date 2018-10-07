#include "Heartbeat.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "tool/Util.h"
#include "log/Log.h"

const std::string& Heartbeat::s_task_name = "Heartbeat";

Heartbeat::Heartbeat(Proc& proc, 
					 unsigned int gap_us,
					 unsigned short service_id,
					 unsigned long long service_update_time,
					 const ServiceConfig::IPInfo& ip_info)
	:	TaskMsgBase(proc, s_task_name, gap_us),
		_service_id(service_id),
		_service_update_time(service_update_time),
		_ip_info(ip_info),
		_is_update_conf(false),
		_is_send(false)
{
	_state = EN_STATE_REQUEST;
}

Heartbeat::~Heartbeat()
{
	
}

int Heartbeat::timeout()
{
	print("timeout");

	auto p =_proc._sc.get_service(_service_id);
	if(p != nullptr)
	{
		B_LOG_INFO << "find, _service_id=" << _service_id;

		for(auto it = p->heartbeat_list.begin(); it != p->heartbeat_list.end(); it++)
		{
			if(it->proc_id == _ip_info.proc_id)
			{
				return on_timeout(p->heartbeat, *it);
			}
		}
		
		for(auto it = p->inservice_list.begin(); it != p->inservice_list.end(); it++)
		{
			if(it->proc_id == _ip_info.proc_id)
			{
				return on_timeout(p->heartbeat, *it);
			}
		}
	}
	else
	{
		B_LOG_INFO << "not find, _service_id=" << _service_id;
	}

}

int Heartbeat::run(void* p)
{
	switch (_state)
	{
	case EN_STATE_REQUEST:
		{
			on_request();
			_proc._task_msg_pool.add(this);
			_state = EN_STATE_RESPONSE;

			print("on_request");
		}
		break;

	case EN_STATE_RESPONSE:
		{
			_end_time_us = Util::get_us();
			_delay_us = _end_time_us - _begin_time_us;
			on_response();

			print("on_response");
		}
		break;

	default:
		B_LOG_ERROR << "error _state=" << _state;	
		print();
		break;
	}

	return 0;
}

void Heartbeat::print(const std::string& prefix)
{
	::TaskMsgBase::print(prefix);
	B_LOG_INFO	<< " _service_id=" << _service_id
				<< ", _service_update_time=" << _service_update_time
				<< ", _ip_info.proc_id=" << _ip_info.proc_id
				<< ", _ip_info.proc_des=" << _ip_info.proc_des
				<< ", _ip_info.in_ip=" << _ip_info.in_ip
				<< ", _ip_info.in_port=" << _ip_info.in_port
				<< ", _ip_info.out_ip=" << _ip_info.out_ip
				<< ", _ip_info.out_port=" << _ip_info.out_port;
}

int Heartbeat::on_request()
{
	std::string conf_json;
	if(_is_update_conf)
	{
		//需要下发配置
		if(_proc._sc.get_service_conf(_service_id, conf_json))
		{
			print("update conf_json");
		}
		else
		{
			print("update conf_json error");
		}
	}

	_request.reset(new Packet(_service_id, 0, 0, 0, 0, _seq_id));
	CenterStack::HeartbeatReq(_request->_body,
							  _proc._config.proc.level,
							  _service_id,
							  _ip_info.proc_id,
							  center::HEARTBEAT,
							  _service_update_time, 
							  conf_json);
	_is_send = _proc._tcp_client_pool.get_client(_ip_info)->send_msg(_request);
	if(_is_send)
	{
		B_LOG_INFO << "send_msg=true, _seq_id=" << _seq_id;
	}
	else
	{
		B_LOG_WARN << "send_msg=false, _seq_id=" << _seq_id;
	}

	return 0;
}

int Heartbeat::on_response()
{
	if(_code != ::common::SUCCESS)
	{
		return 0;
	}

	if(_is_update_conf)
	{
		// 1.配置下发心跳的返回后，无其他操作
		// 2.防止下游接管服务更新配置失败或代码写错更新时间对不上，无限循环下发配置
		return 0;
	}

	update_count();	// 更新计数

	const ::google::protobuf::Any& service_msg = _response->_body.service_msg();
	if(service_msg.Is<center::CenterMsg>())
	{
		center::CenterMsg msg;
		service_msg.UnpackTo(&msg);
		if(msg.choice_case() == center::CenterMsg::kHeartbeatRsp)
		{
			const center::HeartbeatRsp& req = msg.heartbeat_rsp();
			B_LOG_INFO	<< "level=" << req.level()
						<< ", service_id=" << req.service_id()
						<< ", proc_id=" << req.proc_id()
						<< ", conf_update_time=" << req.conf_update_time()
						<< ", expire_second=" << req.expire_second();

			if(req.conf_update_time() != _service_update_time)
			{
				if(	req.level() >= _proc._config.proc.level || 
					req.expire_second() >= _proc._config.proc.level_expire_time)
				{
					// 当前接管的center等级低于当前center的等级, 或
					// 当前接管的过期时间大于等于当前最大接管过期时间，则接管
					Heartbeat* hb = new Heartbeat(_proc,
												  _proc._config.proc.prober_timeout_us,
												  _service_id,
												  _service_update_time,
												  _ip_info);
					hb->_is_update_conf = true;
					hb->run();
				}
			}
		}
	}

	return 0;
}

int Heartbeat::on_timeout(const ServiceConfig::Heartbeat& heartbeat,
						  ServiceConfig::IPInfo& ip_info)
{
	if(!_is_send)
	{
		bool b = _proc._tcp_client_pool.get_client(_ip_info)->reomve_msg_send_buffer(_seq_id);
		if(b)
		{
			B_LOG_INFO << "reomve_msg_send_buffer=true, _seq_id=" << _seq_id;
		}
		else
		{
			B_LOG_INFO << "reomve_msg_send_buffer=false, _seq_id=" << _seq_id;
		}
	}

	ip_info._ip_info_derivative.hb_success_count = 0;
	ip_info._ip_info_derivative.hb_error_count++;

	if(ip_info._ip_info_derivative.hb_error_count >= heartbeat.lose_time)
	{
		if(ip_info._ip_info_derivative.is_run)
		{
			update_is_run(ip_info, false);
		}
	}

	B_LOG_ERROR << "_service_id=" << _service_id
				<< ", _ip_info.proc_id=" << ip_info.proc_id
				<< ", _ip_info.proc_des=" << ip_info.proc_des
				<< ", _ip_info.in_ip=" << ip_info.in_ip
				<< ", _ip_info.in_port=" << ip_info.in_port
				<< ", _ip_info.out_ip=" << ip_info.out_ip
				<< ", _ip_info.out_port=" << ip_info.out_port
				<< ", is_run=" << ip_info._ip_info_derivative.is_run
				<< ", hb_success_count=" <<  ip_info._ip_info_derivative.hb_success_count
				<< ", hb_error_count=" <<  ip_info._ip_info_derivative.hb_error_count
				<< ", update_time=" <<  ip_info._ip_info_derivative.update_time;
	return 0;
}

void Heartbeat::update_count()
{
	auto p =_proc._sc.get_service(_service_id);
	if(p != nullptr)
	{
		B_LOG_INFO << "find, _service_id=" << _service_id;

		for(auto it = p->heartbeat_list.begin(); it != p->heartbeat_list.end(); it++)
		{
			if(it->proc_id == _ip_info.proc_id)
			{
				on_count(p->heartbeat, *it);
				return;
			}
		}

		for(auto it = p->inservice_list.begin(); it != p->inservice_list.end(); it++)
		{
			if(it->proc_id == _ip_info.proc_id)
			{
				on_count(p->heartbeat, *it);
				return;
			}
		}
	}
	else
	{
		B_LOG_INFO << "not find, _service_id=" << _service_id;
	}
}

void Heartbeat::on_count(const ServiceConfig::Heartbeat& heartbeat, 
						 ServiceConfig::IPInfo& ip_info)
{
	if(ip_info._ip_info_derivative.hb_error_count >= heartbeat.lose_time)
	{
		// 如果是踢掉的机器，需等待稳定一下才恢复
		ip_info._ip_info_derivative.hb_success_count++;

		B_LOG_ERROR << "recoving, "
					<< ", _service_id=" << _service_id
					<< ", _ip_info.proc_id=" << ip_info.proc_id
					<< ", hb_success_count=" << ip_info._ip_info_derivative.hb_success_count
					<< ", hb_error_count=" << ip_info._ip_info_derivative.hb_error_count;

		if(ip_info._ip_info_derivative.hb_success_count > heartbeat.recover_time)
		{
			ip_info._ip_info_derivative.hb_error_count = 0;

			B_LOG_ERROR << "recove success, "
						<< ", _service_id=" << _service_id
						<< ", _ip_info.proc_id=" << ip_info.proc_id
						<< ", hb_success_count=" << ip_info._ip_info_derivative.hb_success_count
						<< ", hb_error_count=" << ip_info._ip_info_derivative.hb_error_count;

			if(!ip_info._ip_info_derivative.is_run)
			{
				update_is_run(ip_info, true);
			}
		}
	}
	else
	{
		// 否则立即恢复
		ip_info._ip_info_derivative.hb_error_count = 0;
		ip_info._ip_info_derivative.hb_success_count++;

		if(!ip_info._ip_info_derivative.is_run)
		{
			// 第一次心跳探测
			update_is_run(ip_info, true);
		}
	}

	B_LOG_ERROR << "_service_id=" << _service_id
				<< ", _ip_info.proc_id=" << ip_info.proc_id
				<< ", _ip_info.proc_des=" << ip_info.proc_des
				<< ", _ip_info.in_ip=" << ip_info.in_ip
				<< ", _ip_info.in_port=" << ip_info.in_port
				<< ", _ip_info.out_ip=" << ip_info.out_ip
				<< ", _ip_info.out_port=" << ip_info.out_port
				<< ", is_run=" << ip_info._ip_info_derivative.is_run
				<< ", hb_success_count=" <<  ip_info._ip_info_derivative.hb_success_count
				<< ", hb_error_count=" <<  ip_info._ip_info_derivative.hb_error_count
				<< ", update_time=" <<  ip_info._ip_info_derivative.update_time;
}

void Heartbeat::update_is_run(ServiceConfig::IPInfo& ip_info, bool is_run)
{
	// 更新状态
	ip_info._ip_info_derivative.is_run = is_run;
	ip_info._ip_info_derivative.update_time_now();

	// 如果是上线服务，更新相关依赖服务时间，触发配置下发
	bool b = is_inservice_list();
	if(b)
	{
		update_depend_service_time(ip_info);
	}
}

bool Heartbeat::is_inservice_list()
{
	auto p = _proc._sc.get_service(_service_id);
	if(p != nullptr)
	{
		for(auto it = p->inservice_list.begin(); it != p->inservice_list.end(); it++)
		{
			if(it->proc_id == _ip_info.proc_id)
			{
				return true;
			}
		}
	}

	return false;
}

void Heartbeat::update_depend_service_time(const ServiceConfig::IPInfo& ip_info)
{
	std::map<unsigned short, ServiceConfig::Service>& sc = _proc._sc.get_service_map();
	for(auto it_sc = sc.begin(); it_sc != sc.end(); it_sc++)
	{
		ServiceConfig::Service& service = it_sc->second;
		auto it = service.depend_map.find(_service_id);
		if(it != service.depend_map.end())
		{
			service._service_derivative.set_update_time(ip_info._ip_info_derivative.update_time);
			B_LOG_INFO	<< "depend_service conf update inservice_list"
						<< ", service_id=" << _service_id
						<< ", proc_id=" << _ip_info.proc_id
						<< ", update_time=" << _ip_info._ip_info_derivative.update_time
						<< ", depend_service_id=" << service.service_id
						<< ", depend_service_name=" << service.service_name;
		}
	}
}












