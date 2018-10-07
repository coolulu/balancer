#include "HandleServer.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "handle/server/Heartbeat.h"
#include "core/PacketStream.h"
#include "handle/server/CloseConnId.h"

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

	if(service_msg.Is<gate::GateMsg>())
	{
		gate::GateMsg msg;
		service_msg.UnpackTo(&msg);

		switch(msg.choice_case())
		{
		case gate::GateMsg::kTestReq:
			break;

		case gate::GateMsg::kCloseConnIdReq:
			{
				B_LOG_INFO << "gate::CloseConnIdReq, _msg_seq_id=" << packet_ptr->_msg_seq_id;
				CloseConnId cci(_proc, conn, packet_ptr, time);
				cci.handle(msg);
			}
			break;

		default:
			B_LOG_ERROR << "unknow GateMsg, choice_case=" << msg.choice_case();
			break;
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
	// 修改buffer中conn_seq_id,把client.conn_seq_id替换成service.conn_seq_id,同时修改_check_sum
	const Context& context = boost::any_cast<const Context&>(conn->getContext());
	PacketStreamPtr stream(new PacketStream(packet_ptr));
	stream->set_buffer_conn_seq_id(context._conn_seq_id);

	_proc._gate_server.send_stream(stream);
}
