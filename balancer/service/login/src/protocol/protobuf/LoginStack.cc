#include "LoginStack.h"

void LoginStack::LoginRsp(data::Body& body, int code, const std::string& info)
{
	login::LoginMsg msg;

	login::LoginRsp* rsp = msg.mutable_login_rsp();

	::data::MsgRsp* msg_rsp = body.mutable_msg_rsp();
	msg_rsp->set_code(code);
	msg_rsp->set_info(info);

	body.mutable_service_msg()->PackFrom(msg);
}

void LoginStack::AccessKeyReq(data::Body& body)
{
	login::LoginMsg msg;

	login::AccessKeyReq* req = msg.mutable_access_key_req();

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}
