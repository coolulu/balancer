#include "HandleReq.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"

#include "handle/req/HeartbeatReq.h"

HandleReq::HandleReq(Proc& proc)
	: _proc(proc)
{

}

HandleReq::~HandleReq()
{

}

void HandleReq::handle(const muduo::net::TcpConnectionPtr& conn, 
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
		case center::CenterMsg::kHeartbeatReq:
			{
				B_LOG_INFO << "center::HeartbeatReq, _msg_seq_id=" << packet_ptr->_msg_seq_id;
				HeartbeatReq req(_proc, conn, packet_ptr, time);
				req.handle(msg);
			}
			break;

		default:

			break;
		}

		return;
	}
	
	if(false)
	{
		// ���ر���
		return;
	}
	
	if(false)
	{
		// ��ʼ��δ���
		return;
	}
	
	if(service_msg.Is<navigate::NavigateMsg>())
	{
		
		
	}
	else
	{

	}
}
