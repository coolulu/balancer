#pragma once

#include "core/TaskMsgBase.h"

class DelSession : public TaskMsgBase
{
public:
	DelSession(Proc& proc, unsigned long long conn_seq_id);
	virtual ~DelSession();

public:
	virtual int timeout();
	virtual int run(void* p = nullptr);
	void del_session();

public:
	static const std::string& s_task_name;

private:
	std::string _in_ip;
	int _in_port;
	unsigned long long _conn_seq_id;

};