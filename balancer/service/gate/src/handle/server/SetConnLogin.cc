#include "SetConnLogin.h"

#include "log/Log.h"

SetConnLogin::SetConnLogin(Proc& proc, 
						   const muduo::net::TcpConnectionPtr& conn, 
						   PacketPtr& packet_ptr, 
						   muduo::Timestamp time)
	:	_proc(proc),
		_conn(conn),
		_packet_ptr(packet_ptr),
		_time(time)
{

}

SetConnLogin::~SetConnLogin()
{

}

void SetConnLogin::handle(const gate::GateMsg& msg)
{
	const gate::SetConnLoginReq& req = msg.set_conn_login_req();
	B_LOG_INFO << "conn_id=" << req.conn_id();

	muduo::net::TcpConnectionPtr client_conn;
	bool b = _proc._gate_server.find(req.conn_id(), client_conn);
	if(b)
	{
		GateContext* p_gate_context = boost::any_cast<GateContext>(client_conn->getMutableContext());
		p_gate_context->_en_conn = GateContext::EN_CONN_LOGIN;		// ��������Ϊ��¼״̬

		PacketPtr packet_ptr_rsp(new Packet(_packet_ptr->_from_service_id, 0, 0, 0, 0, _packet_ptr->_msg_seq_id));
		GateStack::SetConnLoginRsp(packet_ptr_rsp->_body, common::SUCCESS, "");

		_proc._tcp_server.send_msg(_conn, packet_ptr_rsp);
	}
	else
	{
		B_LOG_WARN << "SetConnLogin is not find conn, conn_id=" << req.conn_id();
		PacketPtr packet_ptr_rsp(new Packet(_packet_ptr->_from_service_id, 0, 0, 0, 0, _packet_ptr->_msg_seq_id));
		GateStack::SetConnLoginRsp(packet_ptr_rsp->_body, gate::ERR_BUSINESS_NOT_FIND_CONN_ID, "");

		_proc._tcp_server.send_msg(_conn, packet_ptr_rsp);
	}
}
