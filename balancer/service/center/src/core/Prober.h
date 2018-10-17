#pragma once

class Proc;

class Prober
{
public:
	Prober(Proc& proc);
	~Prober();

public:
	void probe();

private:
	Proc& _proc;

};