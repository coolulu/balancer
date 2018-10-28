#include "ProxyStack.h"

void ProxyStack::CheckPasswdReq(data::Body& body, unsigned long long user_id, const std::string& passwd)
{
	proxy::ProxyMsg msg;

	proxy::CheckPasswdReq* req = msg.mutable_check_passwd_req();
	req->set_user_id(user_id);
	req->set_passwd(passwd);

	::data::MsgReq* msg_req = body.mutable_msg_req();

	body.mutable_service_msg()->PackFrom(msg);
}

