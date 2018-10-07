#include "CenterStack.h"

void CenterStack::HeartbeatRsp(data::Body& body,
							   int code,
							   const std::string& info,
							   int level, 
							   int service_id, 
							   unsigned int proc_id, 
							   unsigned long long conf_update_time, 
							   unsigned int expire_second)
{
	center::CenterMsg msg;

	center::HeartbeatRsp* rsp = msg.mutable_heartbeat_rsp();
	rsp->set_level(level);
	rsp->set_service_id(service_id);
	rsp->set_proc_id(proc_id);
	rsp->set_conf_update_time(conf_update_time);
	rsp->set_expire_second(expire_second);

	::data::MsgRsp* msg_rsp = body.mutable_msg_rsp();
	msg_rsp->set_code(code);
	msg_rsp->set_info(info);

	body.mutable_service_msg()->PackFrom(msg);
}
