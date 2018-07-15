#pragma once

#include <map>

class Proc;

struct Probetime
{
	Probetime(unsigned int serv_id) : service_id(serv_id), probe_time(0){}

	unsigned short service_id;
	unsigned int probe_time;
};


class Prober
{
public:
	Prober(Proc& proc);
	~Prober();

public:
	void probe();

private:
	Probetime* get_service_probetime(unsigned short service_id);

private:
	Proc& _proc;
	std::map<unsigned short, Probetime> _service_probetime_map;
};