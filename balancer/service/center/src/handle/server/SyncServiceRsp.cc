#include "SyncServiceRsp.h"

#include "log/Log.h"


SyncServiceRsp::SyncServiceRsp(Proc& proc, 
							   const muduo::net::TcpConnectionPtr& conn,
							   PacketPtr& packet_ptr,
							   muduo::Timestamp time)
	:	_proc(proc),
		_conn(conn),
		_packet_ptr(packet_ptr),
		_time(time)
{

}

SyncServiceRsp::~SyncServiceRsp()
{

}

void SyncServiceRsp::handle(const center::CenterMsg& msg)
{
	const center::SyncServiceReq& req = msg.sync_service_req();
	B_LOG_INFO	<< "conf_update_time=" << req.conf_update_time();

	std::string conf_json;
	unsigned long long update_time = _proc._sc.get_config_derivative().update_time;
	if(update_time != req.conf_update_time())
	{
		conf_json = _proc._sc.map_to_json();
		B_LOG_INFO	<< "update update_time=" << update_time
					<< ", conf_json=" << conf_json;		
	}
	else
	{
		B_LOG_INFO << "not update conf_json";
	}

	PacketPtr packet_ptr_rsp(new Packet(_packet_ptr->_from_service_id, 0, 0, 0, 0, _packet_ptr->_msg_seq_id));
	CenterStack::SyncServiceRsp(packet_ptr_rsp->_body,
								common::SUCCESS,
								"",
								update_time,
								conf_json);

	_proc._tcp_server.send_msg(_conn, packet_ptr_rsp);
}
