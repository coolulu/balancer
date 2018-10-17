#pragma once

class Proc;

class Synchro
{
public:
	Synchro(Proc& proc);
	~Synchro();

public:
	void check_sync();

private:
	Proc& _proc;
	unsigned int _sync_time;
};