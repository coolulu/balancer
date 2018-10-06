#include "GateStack.h"

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

	::data::Body_MsgRsq* msg_rsp = body.mutable_msg_rsp();
	msg_rsp->set_code(code);
	msg_rsp->set_info(info);

	body.mutable_service_msg()->PackFrom(msg);
}
