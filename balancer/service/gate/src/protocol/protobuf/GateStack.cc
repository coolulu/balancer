#include "GateStack.h"

void GateStack::WakeHeartbeatReq(data::Body& body, unsigned long long server_time)
{
	gate::GateMsg msg;

	gate::WakeHeartbeatReq* req = msg.mutable_wake_heartbeat_req();
	req->set_server_time(server_time);

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}

void GateStack::GetConnIdRsp(data::Body& body,
							 int code,
							 const std::string& info,
							 unsigned long long server_time, 
							 unsigned int conn_create_time, 
							 unsigned long long conn_id)
{
	gate::GateMsg msg;

	gate::GetConnIdRsp* rsp = msg.mutable_get_conn_id_rsp();
	rsp->set_server_time(server_time);
	rsp->set_conn_create_time(conn_create_time);
	rsp->set_conn_id(conn_id);

	::data::MsgRsp* msg_rsp = body.mutable_msg_rsp();
	msg_rsp->set_code(code);
	msg_rsp->set_info(info);

	body.mutable_service_msg()->PackFrom(msg);
}

void GateStack::CloseConnIdRsp(data::Body& body, int code, const std::string& info)
{
	gate::GateMsg msg;

	gate::CloseConnIdRsp* rsp = msg.mutable_close_conn_id_rsp();

	::data::MsgRsp* msg_rsp = body.mutable_msg_rsp();
	msg_rsp->set_code(code);
	msg_rsp->set_info(info);

	body.mutable_service_msg()->PackFrom(msg);
}

void GateStack::CloseClientReq(data::Body& body)
{
	gate::GateMsg msg;

	gate::CloseClientReq* req = msg.mutable_close_client_req();

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}

void GateStack::LogoutRsp(data::Body& body, int code, const std::string& info)
{
	gate::GateMsg msg;

	gate::LogoutRsp* rsp = msg.mutable_logout_rsp();

	::data::MsgRsp* msg_rsp = body.mutable_msg_rsp();
	msg_rsp->set_code(code);
	msg_rsp->set_info(info);

	body.mutable_service_msg()->PackFrom(msg);
}

void GateStack::SetConnLoginRsp(data::Body& body, int code, const std::string& info)
{
	gate::GateMsg msg;

	gate::SetConnLoginRsp* rsp = msg.mutable_set_conn_login_rsp();

	::data::MsgRsp* msg_rsp = body.mutable_msg_rsp();
	msg_rsp->set_code(code);
	msg_rsp->set_info(info);

	body.mutable_service_msg()->PackFrom(msg);
}

