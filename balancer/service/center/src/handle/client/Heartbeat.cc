#include "Heartbeat.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "tool/Util.h"
#include "log/Log.h"

Heartbeat::Heartbeat(Proc& proc, 
					 unsigned int gap_us, 
					 unsigned short service_id,
					 const ServiceConfig::IPInfo& ip_info)
	:	TaskMsgBase(proc, std::string("Heartbeat"), gap_us),
		_service_id(service_id),
		_ip_info(ip_info)
{
	_state = EN_STATE_REQUEST;
}

Heartbeat::~Heartbeat()
{
	
}

int Heartbeat::timeout()
{
	print("timeout");
}

int Heartbeat::run(void* p)
{
	switch (_state)
	{
	case EN_STATE_REQUEST:
		{
			on_request();
			_begin_time_us = Util::get_us();
			_proc._task_msg_pool.add(this);
			_state = EN_STATE_RESPONSE;

			print("on_request");
		}
		break;

	case EN_STATE_RESPONSE:
		{
			_end_time_us = Util::get_us();
			_delay_us = _end_time_us - _begin_time_us;
			on_response(p);

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
	B_LOG_INFO	<< " _ip_info.proc_id=" << _ip_info.proc_id
				<< ", _ip_info.proc_des=" << _ip_info.proc_des
				<< ", _ip_info.in_ip=" << _ip_info.in_ip
				<< ", _ip_info.out_ip=" << _ip_info.out_ip
				<< ", _ip_info.port=" << _ip_info.port;
}

int Heartbeat::on_request()
{
	_request.reset(new Packet(_service_id, 0, 0, 0, 0, _seq_id));
	CenterStack::HeartbeatReq(_request->_body,
							  _proc._config.proc.level,
							  _service_id,
							  _ip_info.proc_id,
							  center::HEARTBEAT,
							  time(NULL), 
							  "");
	_proc._tcp_client_pool.get_client(_ip_info)->send_msg(_request);
	return 0;
}

int Heartbeat::on_response(void* p)
{
	_end_time_us = Util::get_us();
	_delay_us = _end_time_us - _begin_time_us;

	const center::CenterMsg& msg = *(center::CenterMsg*)p;
	const center::HeartbeatRsp& req = msg.heartbeat_rsp();
	B_LOG_INFO << "level=" << req.level();
	B_LOG_INFO << "service_id=" << req.service_id();
	B_LOG_INFO << "proc_id=" << req.proc_id();
	B_LOG_INFO << "conf_update_time=" << req.conf_update_time();
	B_LOG_INFO << "expire_second=" << req.expire_second();

	return 0;
}










