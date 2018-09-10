#include "HandleServer.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"

#include "handle/server/Heartbeat.h"

HandleServer::HandleServer(Proc& proc)
	: _proc(proc)
{

}

HandleServer::~HandleServer()
{

}

void HandleServer::handle(const muduo::net::TcpConnectionPtr& conn, 
					   PacketPtr& packet_ptr, 
					   muduo::Timestamp time)
{
	if(packet_ptr->_body.msg_type_case() != data::Body::kMsgReq)
	{
		B_LOG_ERROR << "error msg_type=" << packet_ptr->_body.msg_type_case();
		return;
	}

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
				Heartbeat hb(_proc, conn, packet_ptr, time);
				hb.handle(msg);
			}
			break;

		default:
			B_LOG_ERROR << "unknow CenterMsg, choice_case=" << msg.choice_case();
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
		navigate::NavigateMsg msg;
		service_msg.UnpackTo(&msg);
		
		switch (msg.choice_case())
		{
		case navigate::NavigateMsg::kTestReq:
			
			break;

		default:
			B_LOG_ERROR << "unknow NavigateMsg, choice_case=" << msg.choice_case();
			break;
		}
	}
	else
	{
		B_LOG_ERROR << "unknow service, _msg_seq_id=" << packet_ptr->_msg_seq_id;
		packet_ptr->print();
	}
}
