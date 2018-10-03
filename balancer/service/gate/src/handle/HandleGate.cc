#include "HandleGate.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "core/TaskMsgMaster.h"

HandleGate::HandleGate(Proc& proc)
	: _proc(proc)
{

}

HandleGate::~HandleGate()
{

}

void HandleGate::handle_request(const muduo::net::TcpConnectionPtr& conn, 
								PacketPtr& packet_ptr, 
								muduo::Timestamp time)
{
	const ::google::protobuf::Any& service_msg = packet_ptr->_body.service_msg();

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

	if(service_msg.Is<gate::GateMsg>())
	{
		TaskMsgMaster* task = nullptr;

		gate::GateMsg msg;
		service_msg.UnpackTo(&msg);

		switch(msg.choice_case())
		{
		case gate::GateMsg::kTestReq:
			task = nullptr;
			break;

		default:
			B_LOG_ERROR << "unknow GateMsg, choice_case=" << msg.choice_case();
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

void HandleGate::forward_request_to_service(const muduo::net::TcpConnectionPtr& conn, 
											PacketPtr& packet_ptr, 
											muduo::Timestamp time)
{
	bool b = false;
	ServiceConfig::IPInfo ip_info;
	if(packet_ptr->_to_proc_id == 0)
	{
		b = _proc._is.get_ip_info(packet_ptr->_to_service_id, ip_info);
	}
	else
	{
		b = _proc._is.get_ip_info(packet_ptr->_to_service_id, packet_ptr->_to_proc_id, ip_info);
	}

	if(b)
	{
		_proc._tcp_client_pool.get_client(ip_info)->send_stream(packet_ptr);
	}
	else
	{
		B_LOG_WARN	<< "_is.get_ip_info is false"
					<< ", _msg_seq_id=" << packet_ptr->_msg_seq_id
					<< ", _to_service_id=" << packet_ptr->_to_service_id
					<< ", _to_proc_id=" << packet_ptr->_to_proc_id;
	}
}

void HandleGate::forward_response_to_service(const muduo::net::TcpConnectionPtr& conn, 
											 PacketPtr& packet_ptr, 
											 muduo::Timestamp time)
{
	_proc._tcp_server.send_stream(packet_ptr);
}
