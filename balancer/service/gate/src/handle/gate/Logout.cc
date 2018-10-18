#include "Logout.h"

Logout::Logout(Proc& proc, 
			   const muduo::net::TcpConnectionPtr& conn,
			   PacketPtr& packet_ptr,
			   muduo::Timestamp time)
	:	_proc(proc),
		_conn(conn),
		_packet_ptr(packet_ptr),
		_time(time)
{

}

Logout::~Logout()
{

}

void Logout::handle(const gate::GateMsg& msg)
{
	const gate::LogoutReq& req = msg.logout_req();

	const GateContext& gate_context = boost::any_cast<const GateContext&>(_conn->getContext());
	B_LOG_INFO	<< "client Logout, shutdown"
				<< ", _conn_seq_id=" << gate_context._conn_seq_id 
				<< ", _create_time=" << gate_context._create_time 
				<< ", _update_time=" << gate_context._update_time;

	PacketPtr packet_ptr_rsp(new Packet(_packet_ptr->_from_service_id, 0, 0, 0, _packet_ptr->_msg_seq_id, _packet_ptr->_msg_seq_id));
	GateStack::LogoutRsp(packet_ptr_rsp->_body, common::SUCCESS, "");

	_proc._gate_server.send_msg(_conn, packet_ptr_rsp);

	_conn->shutdown();	// ¹Ø±Õ¿Í»§¶Ë
}