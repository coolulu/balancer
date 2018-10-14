#include "PutLoad.h"

#include "log/Log.h"

PutLoad::PutLoad(Proc& proc,
				 const muduo::net::TcpConnectionPtr& conn,
				 PacketPtr& packet_ptr,
				 muduo::Timestamp time)
	:	_proc(proc),
		_conn(conn),
		_packet_ptr(packet_ptr),
		_time(time)
{

}

PutLoad::~PutLoad()
{

}

void PutLoad::handle(const navigate::NavigateMsg& msg)
{
	const navigate::PutLoadReq& req = msg.put_load_req();
	B_LOG_INFO	<< "service_id=" << req.service_id()
				<< ", proc_id=" << req.proc_id()
				<< ", load_val=" << req.load_val();

	_proc._count_load.update(req.service_id(), req.proc_id(), req.load_val());
}
	

