#include "NavigateStack.h"

void NavigateStack::PutLoadReq(data::Body& body, 
							   int service_id, 
							   unsigned int proc_id, 
							   int load_val)
{
	navigate::NavigateMsg msg;

	navigate::PutLoadReq* req = msg.mutable_put_load_req();
	req->set_service_id(service_id);
	req->set_proc_id(proc_id);
	req->set_load_val(load_val);

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}
