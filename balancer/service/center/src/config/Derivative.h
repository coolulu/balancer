#pragma once

struct ConfigDerivative
{
	ConfigDerivative();

	// 触发config同步
	void sync_config(long long update_time);
	void sync_config();

	unsigned long long update_time;
};

// 触发service同步，则一定要触发config同步
struct ServiceDerivative
{
	ServiceDerivative();

	// 触发service同步
	unsigned long long sync_service(long long update_time);
	unsigned long long sync_service();
	void set_update_time(long long update_time);

	unsigned long long update_time;
	unsigned int probe_time;	//探测时间(秒)
};


struct IPInfoDerivative
{
	IPInfoDerivative();

	unsigned long long update_time_now();

	bool is_run;
	unsigned int hb_success_count;
	unsigned int hb_error_count;
	unsigned long long update_time;
};


