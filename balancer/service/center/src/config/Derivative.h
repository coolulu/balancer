#pragma once

struct ConfigDerivative
{
	ConfigDerivative();

	// ����configͬ��
	void sync_config(long long update_time);
	void sync_config();

	unsigned long long update_time;
};

// ����serviceͬ������һ��Ҫ����configͬ��
struct ServiceDerivative
{
	ServiceDerivative();

	// ����serviceͬ��
	unsigned long long sync_service(long long update_time);
	unsigned long long sync_service();
	void set_update_time(long long update_time);

	unsigned long long update_time;
	unsigned int probe_time;	//̽��ʱ��(��)
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


