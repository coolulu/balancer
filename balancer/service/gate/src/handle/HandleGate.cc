#include "HandleGate.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "handle/gate/GetConnId.h"
#include "handle/gate/Logout.h"

HandleGate::HandleGate(Proc& proc)
	: _proc(proc)
{

}

HandleGate::~HandleGate()
{

}

void HandleGate::handle_request_not_init_conn(const muduo::net::TcpConnectionPtr& conn, 
											  PacketPtr& packet_ptr,
											  muduo::Timestamp time)
{
	const ::google::protobuf::Any& service_msg = packet_ptr->_body.service_msg();

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

	if(service_msg.Is<gate::GateMsg>())
	{
		gate::GateMsg msg;
		service_msg.UnpackTo(&msg);

		switch(msg.choice_case())
		{
		case gate::GateMsg::kGetConnIdReq:
			{
				B_LOG_INFO << "gate::GetConnIdReq, _msg_seq_id=" << packet_ptr->_msg_seq_id;
				GetConnId get_conn_id(_proc, conn, packet_ptr, time);
				get_conn_id.handle(msg);
			}
			break;

		default:
			B_LOG_ERROR << "unknow GateMsg, shutdown, choice_case=" << msg.choice_case();
			conn->shutdown();	// �رտͻ�������
			break;
		}
	}
	else
	{
		B_LOG_ERROR << "unknow service, shutdown, _msg_seq_id=" << packet_ptr->_msg_seq_id;
		packet_ptr->print();
		conn->shutdown();		// �رտͻ�������
	}
}

void HandleGate::handle_request(const muduo::net::TcpConnectionPtr& conn, 
								PacketPtr& packet_ptr, 
								muduo::Timestamp time)
{
	const ::google::protobuf::Any& service_msg = packet_ptr->_body.service_msg();

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

	if(service_msg.Is<gate::GateMsg>())
	{
		gate::GateMsg msg;
		service_msg.UnpackTo(&msg);

		switch(msg.choice_case())
		{
		case gate::GateMsg::kLogoutReq:
			{
				B_LOG_INFO << "gate::LogoutReq, _msg_seq_id=" << packet_ptr->_msg_seq_id;
				Logout logout(_proc, conn, packet_ptr, time);
				logout.handle(msg);
			}
			break;

		default:
			B_LOG_ERROR << "unknow GateMsg, shutdown, choice_case=" << msg.choice_case();
			break;
		}
	}
	else
	{
		B_LOG_ERROR << "unknow service, shutdown, _msg_seq_id=" << packet_ptr->_msg_seq_id;
		packet_ptr->print();
	}
}

void HandleGate::handle_response(const muduo::net::TcpConnectionPtr& conn, 
								 TaskMsgBase* task,
								 muduo::Timestamp time)
{
	const::data::MsgRsp& msg_rsp = task->_response->_body.msg_rsp();
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

	task->finish();
	task->run();
}

void HandleGate::forward_request_to_service(const muduo::net::TcpConnectionPtr& conn, 
											PacketPtr& packet_ptr, 
											muduo::Timestamp time)
{
	ServiceConfig::IPInfo* ip_info = nullptr;
	if(packet_ptr->_to_proc_id == 0)
	{
		ip_info = _proc._is.get_ip_info(packet_ptr->_to_service_id);
	}
	else
	{
		ip_info = _proc._is.get_ip_info(packet_ptr->_to_service_id, packet_ptr->_to_proc_id);
	}

	if(ip_info != nullptr)
	{
		_proc._tcp_client_pool.get_client(*ip_info)->send_stream(packet_ptr);
	}
	else
	{
		B_LOG_WARN	<< "_is.get_ip_info is nullptr"
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



