#pragma once

class Proc;

class PutLoad
{
public:
	PutLoad(Proc& proc);
	~PutLoad();

public:
	void trigger_sync_count();
	void check_sync_gap();

private:
	// 广播给所有navigate
	void broadcast();

private:
	Proc& _proc;
	unsigned int _trigger_count;	// 触发次数
	unsigned int _sync_time;		// 同步时间
};