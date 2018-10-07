#include "HandleClient.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"

HandleClient::HandleClient(Proc& proc)
	: _proc(proc)
{

}

HandleClient::~HandleClient()
{

}

void HandleClient::handle_response(const muduo::net::TcpConnectionPtr& conn, 
								 TaskMsgBase* task,
								 muduo::Timestamp time)
{
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

	task->run();
}

void HandleClient::forward_response_to_client(const muduo::net::TcpConnectionPtr& conn, 
											  PacketPtr& packet_ptr,
											  muduo::Timestamp time)
{
	_proc._gate_server.send_stream(packet_ptr);
}
