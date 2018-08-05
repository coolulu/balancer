#include "HandleClient.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"

#include "handle/client/Heartbeat.h"

HandleClient::HandleClient(Proc& proc)
	: _proc(proc)
{

}

HandleClient::~HandleClient()
{

}

void HandleClient::handle(const muduo::net::TcpConnectionPtr& conn, 
						  TaskMsgBase* task,
						  muduo::Timestamp time)
{
	const ::google::protobuf::Any& service_msg = task->_response->_body.service_msg();
	if(service_msg.Is<center::CenterMsg>())
	{
		center::CenterMsg msg;
		service_msg.UnpackTo(&msg);

		switch(msg.choice_case())
		{
		case center::CenterMsg::kHeartbeatRsp:
			{
				B_LOG_INFO << "center::HeartbeatReq, _msg_seq_id=" << task->_response->_msg_seq_id;
				task->run((void*)&msg);
			}
			break;

		default:

			break;
		}

		return;
	}

}
