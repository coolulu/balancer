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
	// �㲥������navigate
	void broadcast();

private:
	Proc& _proc;
	unsigned int _trigger_count;	// ��������
	unsigned int _sync_time;		// ͬ��ʱ��
};