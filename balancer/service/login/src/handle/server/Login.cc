#include "Login.h"

#include "log/Log.h"
#include "tool/Util.h"

const std::string& Login::s_task_name = "Login";

Login::Login(Proc& proc,
			 const muduo::net::TcpConnectionPtr& conn, 
			 PacketPtr& packet_ptr, 
			 muduo::Timestamp time,
			 const login::LoginMsg& msg)
	:	TaskMsgMaster(proc, s_task_name),
		_conn(conn),
		_time(time),
		is_send_rsp(false)
{
	_request = packet_ptr;
	_req = msg.login_req();
	B_LOG_INFO	<< "service_id" << _req.service_id()
				<< ", proc_id" << _req.proc_id()
				<< ", user_id" << _req.user_id()
				<< ", passwd" << _req.passwd()
				<< ", dev_type" << _req.dev_type()
				<< ", dev_token" << _req.dev_token();
}

Login::~Login()
{

}

int Login::timeout_by_sub(TaskMsgSub& sub)
{
	send_rsp_timeout_by_sub();
	return 1;	// 结束主任流程
}

int Login::timeout()
{
	send_rsp_timeout();
	return 0;
}

int Login::run(void* p)
{
	TaskMsgSub* p_sub = (TaskMsgSub*)p;
	B_LOG_INFO	<< "_task_name=" << _task_name 
				<< ", _seq_id=" << _seq_id 
				<< ", _state=" << _state
				<< ", sub_seq_id=" << (p_sub == nullptr ? 0 : p_sub->_seq_id);
	switch (_state)
	{
	case EN_STATE_INIT:
		_state = handle_init();
		break;

	case EN_STATE_AccessKey:
		_state = handle_AccessKey(*p_sub);
		break;

	case EN_STATE_CheckPasswd:
		_state = handle_CheckPasswd(*p_sub);
		break;

	case EN_STATE_SetConnLogin:
		_state = handle_SetConnLogin(*p_sub);
		break;

	case EN_STATE_QuerySession:
		_state = handle_QuerySession(*p_sub);
		break;

	case EN_STATE_DelSession:
		_state = handle_DelSession(*p_sub);
		break;

	case EN_STATE_CloseConnId:
		_state = handle_CloseConnId(*p_sub);
		break;

	case EN_STATE_CreateSession:
		_state = handle_CreateSession(*p_sub);
		break;

	default:
		_code = login::ERR_SYS_TASK_STATE;
		_info = "unkown state, _task_name=" + _task_name + 
				", _seq_id=" + std::to_string(_seq_id) + 
				", _state=" + std::to_string(_state) +
				", _code=" + std::to_string(_code);
		_state = EN_STATE_ERROR;
		B_LOG_ERROR << _info;
		break;
	}

	if(_state == EN_STATE_SUCCESS)
	{
		send_rsp_success();
		return 1;	// 结束主任流程
	}
	else if(_state == EN_STATE_ERROR)
	{
		send_rsp_error();
		return 1;	// 结束主任流程
	}

	return 0;
}

int Login::handle_init()
{
	B_LOG_INFO	<< "service_id" << _req.service_id()
				<< ", proc_id" << _req.proc_id()
				<< ", user_id" << _req.user_id()
				<< ", passwd" << _req.passwd()
				<< ", dev_type" << _req.dev_type()
				<< ", dev_token" << _req.dev_token();

	if(_req.service_id() == 0)
	{
		_code = login::ERR_INTERFACE_PARAM;
		_info = "login_req service_id is 0";
		return EN_STATE_ERROR;
	}
	else if(_req.proc_id() == 0)
	{
		_code = login::ERR_INTERFACE_PARAM;
		_info = "login_req proc_id is 0";
		return EN_STATE_ERROR;
	}
	else if(_req.user_id() == 0)
	{
		_code = login::ERR_INTERFACE_PARAM;
		_info = "login_req user_id is 0";
		return EN_STATE_ERROR;
	}
	else if(_req.passwd().empty())
	{
		_code = login::ERR_INTERFACE_PARAM;
		_info = "login_req passwd is empty";
		return EN_STATE_ERROR;
	}
	else if(_req.dev_type() == 0)
	{
		_code = login::ERR_INTERFACE_PARAM;
		_info = "login_req dev_type is 0";
		return EN_STATE_ERROR;
	}
	else if(_req.dev_token().empty())
	{
		_code = login::ERR_INTERFACE_PARAM;
		_info = "login_req dev_token is empty";
		return EN_STATE_ERROR;
	}

	// 发送给gate转发给client
	TaskMsgSub* p_sub = new TaskMsgSub(_proc, "AccessKeyReq",  _req.service_id(), _req.proc_id(), this);
	sub_insert(p_sub->_seq_id);
	p_sub->_request.reset(new Packet(
		_request->_from_service_id, 0, 0, 0, _request->_conn_seq_id, p_sub->_seq_id));
	LoginStack::AccessKeyReq(p_sub->_request->_body);
	p_sub->run();

	// 记录clinet连接的gate
	_gate_ip_info = p_sub->_ip_info;

	return EN_STATE_AccessKey;
}

int Login::handle_AccessKey(TaskMsgSub& sub)
{
	if(sub._code != common::SUCCESS)
	{
		_code = sub._code;
		_info = sub._info;
		return EN_STATE_ERROR;
	}

	if(sub_is_empty())
	{
		const ::google::protobuf::Any& service_msg = _response->_body.service_msg();
		if(service_msg.Is<login::LoginMsg>())
		{
			login::LoginMsg msg;
			service_msg.UnpackTo(&msg);
			if(msg.choice_case() == login::LoginMsg::kAccessKeyRsp)
			{
				const login::AccessKeyRsp& rsp = msg.access_key_rsp();

				std::string client_access_key = rsp.access_key();
				if(client_access_key.size() != 40)
				{
					B_LOG_ERROR << "accesss key error, client_access_key.size=" << client_access_key.size();
					_code = login::ERR_BUSINESS_ACCESS_KEY_ERROR;
					return EN_STATE_ERROR;
				}

				const std::string& navigate_key = _proc._is.kv()._navigate_key;
				for(unsigned int i = 0; i != client_access_key.size(); i++)
				{
					client_access_key[i] = client_access_key[i] ^ navigate_key[i % navigate_key.size()];
				}

				std::string str_user_id; 
				str_user_id = client_access_key[18]
							+ client_access_key[20]
							+ client_access_key[16]
							+ client_access_key[22]
							+ client_access_key[14]
							+ client_access_key[24]
							+ client_access_key[12]
							+ client_access_key[26]
							+ client_access_key[10]
							+ client_access_key[28]
							+ client_access_key[8] 
							+ client_access_key[30]
							+ client_access_key[6] 
							+ client_access_key[32]
							+ client_access_key[4] 
							+ client_access_key[34]
							+ client_access_key[2] 
							+ client_access_key[36]
							+ client_access_key[0] 
							+ client_access_key[38];
				unsigned long long user_id = Util::str_2_ull(str_user_id);
				if(user_id != _req.user_id())
				{
					B_LOG_ERROR << "accesss key error, user_id=" << user_id << ", _req.user_id=" << _req.user_id();
					_code = login::ERR_BUSINESS_ACCESS_KEY_ERROR;
					return EN_STATE_ERROR;
				}

				std::string str_last_time; 
				str_last_time = client_access_key[21]
							  + client_access_key[19]
							  + client_access_key[23]
							  + client_access_key[17]
							  + client_access_key[25]
							  + client_access_key[15]
							  + client_access_key[27]
							  + client_access_key[13]
							  + client_access_key[29]
							  + client_access_key[11]
							  + client_access_key[31]
							  + client_access_key[9] 
							  + client_access_key[33]
							  + client_access_key[7] 
							  + client_access_key[35]
							  + client_access_key[5] 
							  + client_access_key[37]
							  + client_access_key[3] 
							  + client_access_key[39]
							  + client_access_key[1];
				unsigned long long last_time = Util::str_2_ull(str_last_time);
				unsigned long long now = Util::get_us();
				if(now > last_time)
				{
					B_LOG_ERROR << "accesss key timeout, last_time=" << last_time << ", now=" << now;
					_code = login::ERR_BUSINESS_ACCESS_KEY_TIMEOUT;
					return EN_STATE_ERROR;
				}

				TaskMsgSub* p_sub = new TaskMsgSub(_proc, "CheckPasswd", service::PROXY, 0, this);
				sub_insert(p_sub->_seq_id);
				p_sub->_request.reset(new Packet(
					p_sub->_depend_service_id, p_sub->_proc_id, 0, 0, 0, p_sub->_seq_id));
				ProxyStack::CheckPasswdReq(p_sub->_request->_body, _req.user_id(), _req.passwd());
				p_sub->run();

				return EN_STATE_CheckPasswd;
			}
		}
	}

	return _state;	// 状态不变
}

int Login::handle_CheckPasswd(TaskMsgSub& sub)
{
	if(sub._code != common::SUCCESS)
	{
		_code = sub._code;
		_info = sub._info;
		return EN_STATE_ERROR;
	}

	if(sub_is_empty())
	{
		TaskMsgSub* p_sub = new TaskMsgSub(_proc, "SetConnLogin", _req.service_id(), _req.proc_id(), this);
		sub_insert(p_sub->_seq_id);
		p_sub->_request.reset(new Packet(
			p_sub->_depend_service_id, p_sub->_proc_id, 0, 0, 0, p_sub->_seq_id));
		GateStack::SetConnLoginReq(p_sub->_request->_body, _request->_conn_seq_id);
		p_sub->run();

		return EN_STATE_SetConnLogin;
	}

	return _state;	// 状态不变
}

int Login::handle_SetConnLogin(TaskMsgSub& sub)
{
	if(sub._code != common::SUCCESS)
	{
		_code = sub._code;
		_info = sub._info;
		return EN_STATE_ERROR;
	}

	if(sub_is_empty())
	{
		TaskMsgSub* p_sub = new TaskMsgSub(_proc, "QuerySession", service::SESSION, 0, this);
		sub_insert(p_sub->_seq_id);
		p_sub->_request.reset(new Packet(
			p_sub->_depend_service_id, p_sub->_proc_id, 0, 0, 0, p_sub->_seq_id));
		SessionStack::QuerySessionReq(p_sub->_request->_body, _req.user_id());
		p_sub->run();

		return EN_STATE_QuerySession;
	}

	return _state;	// 状态不变
}

int Login::handle_QuerySession(TaskMsgSub& sub)
{
	if(sub._code != common::SUCCESS)
	{
		_code = sub._code;
		_info = sub._info;
		return EN_STATE_ERROR;
	}

	if(sub_is_empty())
	{
		const ::google::protobuf::Any& service_msg = _response->_body.service_msg();
		if(service_msg.Is<session::SessionMsg>())
		{
			session::SessionMsg msg;
			service_msg.UnpackTo(&msg);
			if(msg.choice_case() == session::SessionMsg::kQuerySessionRsp)
			{
				const session::QuerySessionRsp& rsp = msg.query_session_rsp();

				if(rsp.session().conn_id() == 0)
				{
					// user_id离线，创建会话
					TaskMsgSub* p_sub = new TaskMsgSub(_proc, "CreateSession", service::SESSION, 0, this);
					sub_insert(p_sub->_seq_id);
					p_sub->_request.reset(new Packet(
						p_sub->_depend_service_id, p_sub->_proc_id, 0, 0, 0, p_sub->_seq_id));
					SessionStack::CreateSessionReq(p_sub->_request->_body,
												   _req.user_id(),
												   _req.service_id(),
												   _req.proc_id(),
												   _gate_ip_info.in_ip,
												   _gate_ip_info.in_port,
												   _request->_conn_seq_id,
												   ::time(nullptr),
												   _request->_version,
												   _request->_app_id,
												   _request->_app_version,
												   _req.dev_type());
					p_sub->run();

					return EN_STATE_CreateSession;
				}
				else
				{
					// user_id在线，删除会话，挤下线
					TaskMsgSub* p_sub = new TaskMsgSub(_proc, "DelSession", service::SESSION, 0, this);
					sub_insert(p_sub->_seq_id);
					p_sub->_request.reset(new Packet(
						p_sub->_depend_service_id, p_sub->_proc_id, 0, 0, 0, p_sub->_seq_id));
					SessionStack::DelSessionReq(p_sub->_request->_body, _req.user_id(), "", 0, 0);
					p_sub->run();

					return EN_STATE_DelSession;
				}
			}
		}
	}

	return _state;	// 状态不变
}

int Login::handle_DelSession(TaskMsgSub& sub)
{
	if(sub._code != common::SUCCESS)
	{
		_code = sub._code;
		_info = sub._info;
		return EN_STATE_ERROR;
	}

	if(sub_is_empty())
	{
		TaskMsgSub* p_sub = new TaskMsgSub(_proc, "CloseConnId", _req.service_id(), _req.proc_id(), this);
		sub_insert(p_sub->_seq_id);
		p_sub->_request.reset(new Packet(
			p_sub->_depend_service_id, p_sub->_proc_id, 0, 0, 0, p_sub->_seq_id));
		GateStack::CloseConnIdReq(p_sub->_request->_body, _request->_conn_seq_id); 
		p_sub->run();

		return EN_STATE_CloseConnId;
	}

	return _state;	// 状态不变
}

int Login::handle_CloseConnId(TaskMsgSub& sub)
{
	if(sub._code != common::SUCCESS)
	{
		_code = sub._code;
		_info = sub._info;
		return EN_STATE_ERROR;
	}

	if(sub_is_empty())
	{
		TaskMsgSub* p_sub = new TaskMsgSub(_proc, "CreateSession", service::SESSION, 0, this);
		sub_insert(p_sub->_seq_id);
		p_sub->_request.reset(new Packet(
			p_sub->_depend_service_id, p_sub->_proc_id, 0, 0, 0, p_sub->_seq_id));
		SessionStack::CreateSessionReq(p_sub->_request->_body,
									   _req.user_id(),
									   _req.service_id(),
									   _req.proc_id(),
									   _gate_ip_info.in_ip,
									   _gate_ip_info.in_port,
									   _request->_conn_seq_id,
									   ::time(nullptr),
									   _request->_version,
									   _request->_app_id,
									   _request->_app_version,
									   _req.dev_type());
		p_sub->run();

		return EN_STATE_CreateSession;
	}

	return _state;	// 状态不变
}

int Login::handle_CreateSession(TaskMsgSub& sub)
{
	if(sub._code != common::SUCCESS)
	{
		_code = sub._code;
		_info = sub._info;
		return EN_STATE_ERROR;
	}

	if(sub_is_empty())
	{
		return EN_STATE_SUCCESS;
	}

	return _state;	// 状态不变
}

void Login::send_rsp_success()
{
	_response.reset(new Packet(_request->_from_service_id, 0, _request->_app_id, _request->_app_version, _request->_conn_seq_id, _seq_id));
	LoginStack::LoginRsp(_response->_body, common::SUCCESS, "");
	_proc._tcp_server.send_msg(_conn, _response);
}

void Login::send_rsp_error()
{
	_response.reset(new Packet(_request->_from_service_id, 0, _request->_app_id, _request->_app_version, _request->_conn_seq_id, _seq_id));
	LoginStack::LoginRsp(_response->_body, _code, _info);
	_proc._tcp_server.send_msg(_conn, _response);
}

void Login::send_rsp_timeout()
{
	_code = login::ERR_INTERFACE_MASTER_TIMEOUT;
	switch (_state)
	{
	case EN_STATE_AccessKey:
		_info = "timeout EN_STATE_AccessKey";
		break;

	case EN_STATE_CheckPasswd:
		_info = "timeout EN_STATE_CheckPasswd";
		break;

	case EN_STATE_SetConnLogin:
		_info = "timeout EN_STATE_SetConnLogin";
		break;

	case EN_STATE_QuerySession:
		_info = "timeout EN_STATE_QuerySession";
		break;

	case EN_STATE_DelSession:
		_info = "timeout EN_STATE_DelSession";
		break;

	case EN_STATE_CloseConnId:
		_info = "timeout EN_STATE_CloseConnId";
		break;

	case EN_STATE_CreateSession:
		_info = "timeout EN_STATE_CreateSession";
		break;

	default:
		_info = "timeout _state unkonw, _state=" + std::to_string(_state);
		break;
	}

	_response.reset(new Packet(_request->_from_service_id, 0, _request->_app_id, _request->_app_version, _request->_conn_seq_id, _seq_id));
	LoginStack::LoginRsp(_response->_body, _code, _info);
	_proc._tcp_server.send_msg(_conn, _response);
}

void Login::send_rsp_timeout_by_sub()
{
	_code = login::ERR_INTERFACE_SUB_TIMEOUT;
	switch (_state)
	{
	case EN_STATE_AccessKey:
		_info = "sub timeout EN_STATE_AccessKey";
		break;

	case EN_STATE_CheckPasswd:
		_info = "sub timeout EN_STATE_CheckPasswd";
		break;

	case EN_STATE_SetConnLogin:
		_info = "sub timeout EN_STATE_SetConnLogin";
		break;

	case EN_STATE_QuerySession:
		_info = "sub timeout EN_STATE_QuerySession";
		break;

	case EN_STATE_DelSession:
		_info = "sub timeout EN_STATE_DelSession";
		break;

	case EN_STATE_CloseConnId:
		_info = "sub timeout EN_STATE_CloseConnId";
		break;

	case EN_STATE_CreateSession:
		_info = "sub timeout EN_STATE_CreateSession";
		break;

	default:
		_info = "timeout _state unkonw, _state=" + std::to_string(_state);
		break;
	}

	_response.reset(new Packet(_request->_from_service_id, 0, _request->_app_id, _request->_app_version, _request->_conn_seq_id, _seq_id));
	LoginStack::LoginRsp(_response->_body, _code, _info);
	_proc._tcp_server.send_msg(_conn, _response);
}

