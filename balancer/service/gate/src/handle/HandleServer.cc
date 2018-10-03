#include "HandleServer.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "core/TaskMsgMaster.h"
#include "handle/server/Heartbeat.h"
#include "core/PacketStream.h"

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
				// ���붨ʱ��
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

void HandleServer::forward_request_to_client(const muduo::net::TcpConnectionPtr& conn, 
											 PacketPtr& packet_ptr,
											 muduo::Timestamp time)
{
	// �޸�buffer��conn_seq_id,��client.conn_seq_id�滻��service.conn_seq_id,ͬʱ�޸�_check_sum
	const Context& context = boost::any_cast<const Context&>(conn->getContext());
	PacketStreamPtr stream(new PacketStream(packet_ptr));
	stream->set_buffer_conn_seq_id(context._conn_seq_id);

	_proc._gate_server.send_stream(stream);
}
