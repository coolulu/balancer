#include "HandleServer.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"

#include "handle/server/SyncServiceRsp.h"

HandleServer::HandleServer(Proc& proc)
	: _proc(proc)
{

}

HandleServer::~HandleServer()
{

}

void HandleServer::handle_request(const muduo::net::TcpConnectionPtr& conn, 
								  PacketPtr& packet_ptr, 
								  muduo::Timestamp time)
{
	const ::google::protobuf::Any& service_msg = packet_ptr->_body.service_msg();
	if(service_msg.Is<center::CenterMsg>())
	{
		center::CenterMsg msg;
		service_msg.UnpackTo(&msg);

		switch(msg.choice_case())
		{
		case center::CenterMsg::kSyncServiceReq:
			{
				B_LOG_INFO << "center::SyncServiceReq, _msg_seq_id=" << packet_ptr->_msg_seq_id;
				SyncServiceRsp ss(_proc, conn, packet_ptr, time);
				ss.handle(msg);
			}
			break;

		default:
			B_LOG_ERROR << "unknow CenterMsg, choice_case=" << msg.choice_case();
			break;
		}
	}
	else
	{
		B_LOG_ERROR << "unknow service, _msg_seq_id=" << packet_ptr->_msg_seq_id;
		packet_ptr->print();
	}
}
