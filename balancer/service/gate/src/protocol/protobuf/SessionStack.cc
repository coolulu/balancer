#include "SessionStack.h"

void SessionStack::DelSessionReq(data::Body& body, 
								 unsigned long long user_id, 
								 const std::string& in_ip,
								 int in_port,
								 unsigned int conn_id)
{
	session::SessionMsg msg;

	session::DelSessionReq* req = msg.mutable_del_session_req();
	if(user_id != 0)
	{
		req->set_user_id(user_id);
	}
	else
	{
		session::ConnKey* conn_key = req->mutable_conn_key();
		conn_key->set_in_ip(in_ip);
		conn_key->set_in_port(in_port);
		conn_key->set_conn_id(conn_id);
	}

	::data::Body_MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}
