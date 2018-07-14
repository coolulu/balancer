#include "HandleReq.h"

#include "Proc.h"
#include "protocol/Protocol.h"

#include "handle/req/Heartbeat.h"

HandleReq::HandleReq(BTcpServer& tcp_server)
	: _tcp_server(tcp_server)
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
				Heartbeat hb(_tcp_server, conn, packet_ptr, time);
				hb.handle(msg);
			}
			break;

		default:

			break;
		}

		return;
	}
	
	if(false)
	{
		// 过载保护
		return;
	}
	
	if(false)
	{
		// 初始化未完成
		return;
	}
	
	if(service_msg.Is<navigate::NavigateMsg>())
	{
		
		
	}
	else
	{

	}
}
