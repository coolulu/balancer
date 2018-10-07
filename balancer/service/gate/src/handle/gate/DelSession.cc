#include "DelSession.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "tool/Util.h"
#include "log/Log.h"
#include "core/GateServer.h"

const std::string& DelSession::s_task_name = "DelSession";

DelSession::DelSession(Proc& proc, unsigned long long conn_seq_id)
	:	TaskMsgBase(proc, s_task_name, proc._config.proc.del_session_timeout_us),
		_in_ip(proc._config.proc.local_ip),
		_in_port(proc._config.net.tcp.port),
		_conn_seq_id(conn_seq_id)
{

}

DelSession::~DelSession()
{

}

int DelSession::timeout()
{
	B_LOG_WARN	<< "DelSession is timeout, _in_ip=" << _in_ip
				<< ", _in_port=" << _in_port
				<< ", _conn_seq_id=" << _conn_seq_id;
}

int DelSession::run(void* p)
{
	if(_code == ::common::SUCCESS)
	{
		B_LOG_INFO	<< "DelSession is ok, _in_ip=" << _in_ip
					<< ", _in_port=" << _in_port
					<< ", _conn_seq_id=" << _conn_seq_id;
	}
	else
	{
		B_LOG_WARN	<< "DelSession is error, _in_ip=" << _in_ip
					<< ", _in_port=" << _in_port
					<< ", _conn_seq_id=" << _conn_seq_id
					<< ", _code=" << _code
					<< ", _info=" << _info;
	}
}

void DelSession::del_session()
{
	_request.reset(new Packet(service::SESSION, 0, 0, 0, 0, _seq_id));
	SessionStack::DelSessionReq(_request->_body, 0, _in_ip, _in_port, _conn_seq_id);

	ServiceConfig::IPInfo ip_info;
	bool b = _proc._is.get_ip_info(_request->_to_service_id, ip_info);
	if(b)
	{
		_proc._tcp_client_pool.get_client(ip_info)->send_msg(_request);
	}
	else
	{
		B_LOG_WARN	<< "_is.get_ip_info is false"
					<< ", _msg_seq_id=" << _request->_msg_seq_id
					<< ", _to_service_id=" << _request->_to_service_id
					<< ", _to_proc_id=" << _request->_to_proc_id;
	}

	_proc._task_msg_pool.add(this);					// 加入定时器
}
