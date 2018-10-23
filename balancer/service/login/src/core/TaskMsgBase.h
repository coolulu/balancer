#pragma once

#include <string>

#include "core/Packet.h"

class Proc;

class TaskMsgBase
{
public:
	TaskMsgBase(Proc& proc, 
				const std::string& task_name, 
				unsigned int gap_us);
	virtual ~TaskMsgBase();

public:
	bool check_timeout(unsigned long long now_us);
	void finish();
	virtual int timeout() = 0;
	virtual int run(void* p = nullptr) = 0;
	virtual void print(const std::string& prefix = "");

public:
	static bool is_empty(){return s_count == 0;}
	static int count(){return s_count;}

private:
	static int s_count;

public:
	Proc& _proc;

	const std::string& _task_name;
	const unsigned long long _seq_id;
	unsigned int _gap_us;
	bool _is_timeout;
	unsigned long long _begin_time_us;
	unsigned long long _end_time_us;
	unsigned long long _delay_us;

	int _state;
	int _code;
	std::string _info;
	PacketPtr _request;
	PacketPtr _response;
};
