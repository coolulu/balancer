#pragma once

class Proc;

class Timer
{
public:
	Timer(Proc& proc);
	~Timer();

public:
	void check_timeout();

private:
	Proc& _proc;
};