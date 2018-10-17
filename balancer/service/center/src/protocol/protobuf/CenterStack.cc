#include "CenterStack.h"

void CenterStack::HeartbeatReq(data::Body& body, 
							   int level, 
							   int service_id, 
							   unsigned int proc_id,
							   unsigned int state,
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

void CenterStack::SyncServiceReq(data::Body& body, 
								 unsigned long long conf_update_time)
{
	center::CenterMsg msg;

	center::SyncServiceReq* req = msg.mutable_sync_service_req();
	req->set_conf_update_time(conf_update_time);

	body.mutable_msg_req();
	body.mutable_service_msg()->PackFrom(msg);
}

void CenterStack::SyncServiceRsp(data::Body& body, 
								 int code, 
								 const std::string& info, 
								 unsigned long long conf_update_time, 
								 const std::string& conf_json)
{
	center::CenterMsg msg;

	center::SyncServiceRsp* rsp = msg.mutable_sync_service_rsp();
	rsp->set_conf_update_time(conf_update_time);
	rsp->set_conf_json(conf_json);

	::data::MsgRsp* msg_rsp = body.mutable_msg_rsp();
	msg_rsp->set_code(code);
	msg_rsp->set_info(info);

	body.mutable_service_msg()->PackFrom(msg);
}
