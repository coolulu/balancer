#pragma once

#include <map>

class Proc;

class Prober
{
public:
	Prober(Proc& proc);
	~Prober();

public:
	void probe(unsigned long long now_us);

private:
	Proc& _proc;

};