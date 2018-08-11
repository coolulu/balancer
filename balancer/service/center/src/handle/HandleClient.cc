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
	if(task->_response->_body.msg_type_case() != data::Body::kMsgRsp)
	{
		B_LOG_ERROR << "error msg_type=" << task->_response->_body.msg_type_case();
		return;
	}

	const::data::Body_MsgRsq& msg_rsp = task->_response->_body.msg_rsp();
	task->_code = msg_rsp.code();
	task->_info = msg_rsp.info();

	if(task->_code != ::common::SUCCESS)
	{
		B_LOG_ERROR	<< "_code is not success"
					<< ", _task_name=" << task->_task_name 
					<< ", _seq_id=" << task->_seq_id 
					<< ", _code=" << task->_code 
					<< ", _info=" << task->_info;
	}

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
