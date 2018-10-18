#include "GetConnId.h"

#include "tool/Util.h"

GetConnId::GetConnId(Proc& proc, 
					 const muduo::net::TcpConnectionPtr& conn, 
					 PacketPtr& packet_ptr, 
					 muduo::Timestamp time)
	:	_proc(proc),
		_conn(conn),
		_packet_ptr(packet_ptr),
		_time(time)
{

}

GetConnId::~GetConnId()
{

}

void GetConnId::handle(const gate::GateMsg& msg)
{
	const gate::GetConnIdReq& req = msg.get_conn_id_req();
	B_LOG_INFO << "client_time=" << req.client_time();

	GateContext* p_gate_context = boost::any_cast<GateContext>(_conn->getMutableContext());
	p_gate_context->_is_client_init_conn_seq_id = true;		// client已获取到conn_seq_id，连接可以开始处理业务

	unsigned long long server_time = Util::get_us();
	unsigned int conn_create_time = p_gate_context->_create_time;
	unsigned long long conn_id = p_gate_context->_conn_seq_id;
	B_LOG_INFO	<< "server_time=" << server_time 
				<< ", conn_create_time=" << conn_create_time 
				<< ", conn_id=" << conn_id;

	PacketPtr packet_ptr_rsp(new Packet(_packet_ptr->_from_service_id, 0, 0, 0, _packet_ptr->_msg_seq_id, _packet_ptr->_msg_seq_id));
	GateStack::GetConnIdRsp(packet_ptr_rsp->_body,
							common::SUCCESS,
							"",
							server_time,
							conn_create_time,
							conn_id);

	_proc._gate_server.send_msg(_conn, packet_ptr_rsp);
}
