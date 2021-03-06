#include "HandleServer.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"

#include "handle/server/Heartbeat.h"
#include "handle/server/PutLoad.h"

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
			{
				B_LOG_INFO << "navigate::PutLoadReq, _msg_seq_id=" << packet_ptr->_msg_seq_id;
				PutLoad pl(_proc, conn, packet_ptr, time);
				pl.handle(msg);
			}
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
