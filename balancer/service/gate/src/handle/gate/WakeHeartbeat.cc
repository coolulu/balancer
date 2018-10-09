#include "WakeHeartbeat.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "tool/Util.h"
#include "log/Log.h"
#include "core/GateServer.h"

const std::string& WakeHeartbeat::s_task_name = "WakeHeartbeat";

WakeHeartbeat::WakeHeartbeat(Proc& proc, unsigned long long conn_seq_id)
	:	TaskMsgBase(proc, s_task_name, proc._config.proc.wake_heartbeat_timeout_us),
		_conn_seq_id(conn_seq_id),
		_server_time(_begin_time_us)
{

}

WakeHeartbeat::~WakeHeartbeat()
{

}

int WakeHeartbeat::timeout()
{
	muduo::net::TcpConnectionPtr conn;
	bool b = _proc._gate_server.find(_conn_seq_id, conn);
	if(b)
	{
		B_LOG_WARN << conn->name() << " is idle, shutdown, WakeHeartbeat timeout, _conn_seq_id=" << _conn_seq_id;
		conn->shutdown();	// 关闭客户端连接
	}
	else
	{
		B_LOG_WARN << "not find conn, WakeHeartbeat timeout, _conn_seq_id=" << _conn_seq_id;
	}

	return 0;
}

int WakeHeartbeat::run(void* p)
{
	muduo::net::TcpConnectionPtr conn;
	bool b = _proc._gate_server.find(_conn_seq_id, conn);
	if(!b)
	{
		B_LOG_WARN << "not find conn, WakeHeartbeat rsp, _conn_seq_id=" << _conn_seq_id;
		return 0;
	}

	if(_code == ::common::SUCCESS)
	{
		const ::google::protobuf::Any& service_msg = _response->_body.service_msg();
		if(service_msg.Is<gate::GateMsg>())
		{
			gate::GateMsg msg;
			service_msg.UnpackTo(&msg);
			if(msg.choice_case() == gate::GateMsg::kWakeHeartbeatRsp)
			{
				const gate::WakeHeartbeatRsp& rsp = msg.wake_heartbeat_rsp();

				B_LOG_INFO	<< "WakeHeartbeat rsp, _conn_seq_id=" << _conn_seq_id
							<< ", client_time=" << rsp.client_time()
							<< ", key=" << rsp.key();

				if(rsp.key() ^ _server_time == _conn_seq_id)
				{
					B_LOG_INFO << "key is ok";
					GateContext* p_gate_context = boost::any_cast<GateContext>(conn->getMutableContext());
					p_gate_context->_is_wake_heartbeat_wait = false;	// 状态还原

					return 0;
				}
				else
				{
					B_LOG_WARN << "key is error";
				}
			}
		}
	}

	B_LOG_WARN << conn->name() << " shutdown, _conn_seq_id=" << _conn_seq_id;
	conn->shutdown();	// 关闭客户端连接

	return 0;
}

void WakeHeartbeat::wake_client(muduo::net::TcpConnectionPtr& conn, GateContext* p_gate_context)
{
	_request.reset(new Packet(service::CLIENT, 0, 0, 0, 0, _seq_id));
	GateStack::WakeHeartbeatReq(_request->_body, _server_time);
	_proc._gate_server.send_msg(conn, _request);
	
	p_gate_context->_is_wake_heartbeat_wait = true;	// 设置为等待客户端心跳回复
}
