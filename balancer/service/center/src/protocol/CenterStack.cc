#include "CenterStack.h"

void CenterStack::HeartbeatReq(data::Body& body, 
							   int level, 
							   int service_id, 
							   unsigned int proc_id,
							   center::HeartbeatReq_State state, 
							   unsigned long long conf_update_time, 
							   const std::string& conf_json)
{
	center::CenterMsg msg;

	center::HeartbeatReq* req = msg.mutable_heartbeat_req();
	req->set_level(level);
	req->set_service_id(service_id);
	req->set_proc_id(proc_id);
	req->set_state(state);
	req->set_conf_update_time(conf_update_time);
	req->set_conf_json(conf_json);

	body.mutable_msg_req();
	body.mutable_service_msg()->PackFrom(msg);
}
