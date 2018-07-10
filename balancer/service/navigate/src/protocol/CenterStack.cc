#include "CenterStack.h"

void CenterStack::HeartbeatRsp(data::Body& body, 
							   int level, 
							   int service_id, 
							   unsigned int proc_id, 
							   unsigned long long conf_update_time, 
							   unsigned int role_expire_time)
{
	center::CenterMsg msg;

	center::HeartbeatRsp* rsp = msg.mutable_heartbeat_rsp();
	rsp->set_level(level);
	rsp->set_service_id(service_id);
	rsp->set_proc_id(proc_id);
	rsp->set_conf_update_time(conf_update_time);
	rsp->set_role_expire_time(role_expire_time);

	body.mutable_service_msg()->PackFrom(msg);
}
