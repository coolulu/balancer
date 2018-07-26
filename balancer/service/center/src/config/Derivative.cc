#include "Derivative.h"
#include "tool/Util.h"

ConfigDerivative::ConfigDerivative()
	:	update_time(Util::get_us())
{

}

void ConfigDerivative::sync_config(long long update_time)
{
	this->update_time = update_time;
}

void ConfigDerivative::sync_config()
{
	update_time = Util::get_us();
}


ServiceDerivative::ServiceDerivative()
	:	update_time(Util::get_us()),
		probe_time(0)
{

}

unsigned long long ServiceDerivative::sync_service(long long update_time)
{
	this->update_time = update_time;
}

unsigned long long ServiceDerivative::sync_service()
{
	return update_time = Util::get_us();
}


IPInfoDerivative::IPInfoDerivative()
	:	is_run(false),
		heartbeat_success_count(0),
		heartbeat_error_count(0),
		recover_count(0),
		update_time(Util::get_us())
{

}

unsigned long long IPInfoDerivative::update_time_now()
{
	return update_time = Util::get_us();
}
