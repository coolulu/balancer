#include "SessionStack.h"

void SessionStack::QuerySessionReq(data::Body& body, unsigned long long user_id)
{
	session::SessionMsg msg;

	session::QuerySessionReq* req = msg.mutable_query_session_req();
	req->set_user_id(user_id);

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}

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

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}

void SessionStack::CreateSessionReq(data::Body& body, 
									unsigned long long user_id, 
									int service_id, 
									unsigned int proc_id, 
									const std::string& in_ip, 
									int in_port, 
									unsigned long long conn_id, 
									unsigned int create_time, 
									int version, 
									unsigned int app_id, 
									unsigned int app_version, 
									unsigned int dev_type)
{
	session::SessionMsg msg;

	session::CreateSessionReq* req = msg.mutable_create_session_req();
	session::Session* s = req->mutable_session();
	s->set_user_id(user_id);
	s->set_service_id(service_id);
	s->set_proc_id(proc_id);
	s->set_in_ip(in_ip);
	s->set_in_port(in_port);
	s->set_conn_id(conn_id);
	s->set_create_time(create_time);
	s->set_version(version);
	s->set_app_id(app_id);
	s->set_app_version(app_version);
	s->set_dev_type(dev_type);

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}

