#include "CloseConnId.h"

#include "log/Log.h"
#include "handle/gate/CloseClient.h"

CloseConnId::CloseConnId(Proc& proc, 
						 const muduo::net::TcpConnectionPtr& conn, 
						 PacketPtr& packet_ptr, 
						 muduo::Timestamp time)
	:	_proc(proc),
		_conn(conn),
		_packet_ptr(packet_ptr),
		_time(time)
{

}

CloseConnId::~CloseConnId()
{

}

void CloseConnId::handle(const gate::GateMsg& msg)
{
	const gate::CloseConnIdReq& req = msg.close_conn_id_req();
	B_LOG_INFO << "conn_id=" << req.conn_id();

	muduo::net::TcpConnectionPtr client_conn;
	bool b = _proc._gate_server.find(req.conn_id(), client_conn);
	if(b)
	{
		CloseClient* cc = new CloseClient(_proc, _packet_ptr, req.conn_id(),
										  boost::any_cast<const Context&>(_conn->getContext())._conn_seq_id);
		cc->close_client(client_conn);
		_proc._task_msg_pool.add(cc);	// 加入定时器
	}
	else
	{
		B_LOG_WARN << "CloseConnId is not find conn, conn_id=" << req.conn_id();
		PacketPtr packet_ptr_rsp(new Packet(_packet_ptr->_from_service_id, 0, _packet_ptr->_app_id, _packet_ptr->_app_version, _packet_ptr->_conn_seq_id, _packet_ptr->_msg_seq_id));
		GateStack::CloseConnIdRsp(packet_ptr_rsp->_body, common::SUCCESS, "");

		_proc._tcp_server.send_msg(_conn, packet_ptr_rsp);
	}
}
