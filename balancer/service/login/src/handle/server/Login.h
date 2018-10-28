#pragma once

#include "core/Packet.h"
#include "core/Proc.h"
#include "protocol/Protocol.h"
#include "core/TaskMsgMaster.h"
#include "core/TaskMsgSub.h"

class Login : public TaskMsgMaster
{
public:
	Login(Proc& proc, 
		  const muduo::net::TcpConnectionPtr& conn,
		  PacketPtr& packet_ptr,
		  muduo::Timestamp time,
		  const login::LoginMsg& msg);
	virtual ~Login();

public:
	static const std::string& s_task_name;

	enum EN_STATE
	{
		EN_STATE_INIT			=  0,	// 任务初始化
		EN_STATE_SUCCESS		= -1,	// 任务正常结束
		EN_STATE_ERROR			= -2,	// 任务错误结束
		EN_STATE_TIMEOUT		= -3,	// 主任务超时结束
		EN_STATE_TIMEOUT_BY_SUB	= -4,	// 子任务超时结束

		EN_STATE_AccessKey		=  1,
		EN_STATE_CheckPasswd	=  2,
		EN_STATE_SetConnLogin	=  3,
		EN_STATE_QuerySession	=  4,
		EN_STATE_DelSession		=  5,
		EN_STATE_CloseConnId	=  6,
		EN_STATE_CreateSession	=  7,
	};

public:
	virtual int timeout_by_sub(TaskMsgSub& sub);
	virtual int timeout();
	virtual int run(void* p = nullptr);
	virtual void print(const std::string& prefix = ""){}

public:
	int handle_init();
	int handle_AccessKey(TaskMsgSub& sub);
	int handle_CheckPasswd(TaskMsgSub& sub);
	int handle_SetConnLogin(TaskMsgSub& sub);
	int handle_QuerySession(TaskMsgSub& sub);
	int handle_DelSession(TaskMsgSub& sub);
	int handle_CloseConnId(TaskMsgSub& sub);
	int handle_CreateSession(TaskMsgSub& sub);

	void send_rsp_success();
	void send_rsp_error();
	void send_rsp_timeout();
	void send_rsp_timeout_by_sub();

public:


private:
	const muduo::net::TcpConnectionPtr& _conn;
	muduo::Timestamp _time;

	bool is_send_rsp;
	login::LoginReq _req;
	
	ServiceConfig::IPInfo _gate_ip_info;

};