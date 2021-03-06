#include "CloseClient.h"
#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "tool/Util.h"
#include "log/Log.h"

const std::string& CloseClient::s_task_name = "CloseClient";

CloseClient::CloseClient(Proc& proc, 
						 PacketPtr& packet_ptr_req,
						 unsigned long long client_conn_id,
						 unsigned long long rsp_conn_id)
	:	TaskMsgBase(proc, s_task_name, proc._config.proc.close_client_timeout_us),
		_packet_ptr_req(packet_ptr_req),
		_client_conn_id(client_conn_id),
		_rsp_conn_id(rsp_conn_id)
{

}

CloseClient::~CloseClient()
{

}

int CloseClient::timeout()
{
	handle(true);
	return 0;
}

int CloseClient::run(void* p)
{
	handle(false);
	return 0;
}

void CloseClient::close_client(muduo::net::TcpConnectionPtr& conn)
{
	_request.reset(new Packet(service::CLIENT, 0, 0, 0, 0, _seq_id));
	GateStack::CloseClientReq(_request->_body);
	_proc._gate_server.send_msg(conn, _request);
}

void CloseClient::handle(bool is_timeout)
{
	if(is_timeout)
	{
		B_LOG_WARN	<< "CloseClient is timeout, _client_conn_id=" << _client_conn_id
					<< ", _rsp_conn_id=" << _rsp_conn_id;
	}
	else
	{
		B_LOG_INFO	<< "CloseClient is rsp, _client_conn_id=" << _client_conn_id
					<< ", _rsp_conn_id=" << _rsp_conn_id;
	}

	// 找到客户端连接，关闭客户端连接
	muduo::net::TcpConnectionPtr client_conn;
	bool b = _proc._gate_server.find(_client_conn_id, client_conn);
	if(b)
	{
		B_LOG_INFO << "CloseClient is find conn, shutdown, _client_conn_id=" << _client_conn_id;
		client_conn->shutdown();	// 关闭客户端连接
	}
	else
	{
		B_LOG_WARN << "CloseClient is not find conn, _client_conn_id=" << _client_conn_id;
	}
	
	// 发送rsp
	PacketPtr packet_ptr_rsp(new Packet(_packet_ptr_req->_from_service_id, 0, _packet_ptr_req->_app_id, _packet_ptr_req->_app_version, _packet_ptr_req->_conn_seq_id, _packet_ptr_req->_msg_seq_id));
	GateStack::CloseConnIdRsp(packet_ptr_rsp->_body, common::SUCCESS, "");

	_proc._tcp_server.send_msg(_rsp_conn_id, packet_ptr_rsp);

}
