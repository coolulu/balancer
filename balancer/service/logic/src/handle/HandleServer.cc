#include "HandleServer.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"

#include "handle/server/Heartbeat.h"
#include "core/TaskMsgMaster.h"

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
	
	if(service_msg.Is<logic::LogicMsg>())
	{
		TaskMsgMaster* task = nullptr;

		logic::LogicMsg msg;
		service_msg.UnpackTo(&msg);
		
		switch(msg.choice_case())
		{
		case logic::LogicMsg::kTestReq:
			task = nullptr;
			break;

		default:
			B_LOG_ERROR << "unknow LogicMsg, choice_case=" << msg.choice_case();
			break;
		}

		if(task != nullptr)
		{
			int ret = task->run((void*)&msg);
			if(ret == 0)
			{
				// 加入定时器
				_proc._task_msg_pool.add(task);
			}
			else
			{
				delete task;
				task = nullptr;
			}
		}
	}
	else
	{
		B_LOG_ERROR << "unknow service, _msg_seq_id=" << packet_ptr->_msg_seq_id;
		packet_ptr->print();
	}
}
