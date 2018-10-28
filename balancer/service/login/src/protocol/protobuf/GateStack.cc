#include "GateStack.h"

void GateStack::CloseConnIdReq(data::Body& body, unsigned long long conn_id)
{
	gate::GateMsg msg;

	gate::CloseConnIdReq* req = msg.mutable_close_conn_id_req();
	req->set_conn_id(conn_id);

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}

void GateStack::SetConnLoginReq(data::Body& body, unsigned long long conn_id)
{
	gate::GateMsg msg;

	gate::SetConnLoginReq* req = msg.mutable_set_conn_login_req();
	req->set_conn_id(conn_id);

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}

