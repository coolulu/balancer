#include "HeartbeatReq.h"

#include "log/Log.h"
#include "define.h"

HeartbeatReq::HeartbeatReq(Proc& proc,
						   const muduo::net::TcpConnectionPtr& conn, 
						   PacketPtr& packet_ptr, 
						   muduo::Timestamp time)
	:	_proc(proc),
		_conn(conn),
		_packet_ptr(packet_ptr),
		_time(time)
{

}

HeartbeatReq::~HeartbeatReq()
{

}

void HeartbeatReq::handle(const center::CenterMsg& msg)
{
	const center::HeartbeatReq& req = msg.heartbeat_req();
	B_LOG_INFO << "level=" << req.level();
	B_LOG_INFO << "service_id=" << req.service_id();
	B_LOG_INFO << "proc_id=" << req.proc_id();
	B_LOG_INFO << "state=" << req.state();
	B_LOG_INFO << "conf_update_time=" << req.conf_update_time();
	B_LOG_INFO << "conf_json=" << req.conf_json();

	if(req.service_id() != Define::service_id)
	{
		B_LOG_ERROR << "unknow service_id=" << req.service_id();
		return;
	}

	_proc._owner.update_owner_hb_time(req.level(), req.state());
	if(req.conf_json().size() > 0)
	{
		// ��������
		ServiceConfig sc;
		std::string err = sc.json_to_map(req.conf_json());
		if(err.empty())
		{
			_proc._sc.assign(sc);


			_proc._owner.update_owner(req.level(), req.conf_update_time(), _packet_ptr->_msg_seq_id);
		}
	}

	PacketPtr packet_ptr_rsp(new Packet(_packet_ptr->_from_service_id, 0, 0, 0, 0, _packet_ptr->_msg_seq_id));
	CenterStack::HeartbeatRsp(packet_ptr_rsp->_body,
		common::SUCCESS,
		"",
		req.level(),
		req.service_id(),
		req.proc_id(),
		_proc._owner._conf_update_time,
		_proc._owner._expire_second);

	_proc._tcp_server.send_msg(_conn, packet_ptr_rsp);
}


