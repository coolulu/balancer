#pragma once

#include <string>

namespace Util
{
	int get_local_ip(const char *pEthName,int& local_ip);
	const char* bin2hex(const char* buf,int len);
	char char2int(char ch);
	const int hex2bin(const char* hex_str,char* buf,int& len);
	unsigned sip_2_uip(const char* s_ip);
	std::string uip_2_sip(unsigned uip);
	int bin_2_file(const std::string &filepath,const char* ptr,int filelen);
	int file_2_bin(const std::string &filepath,char* ptr, unsigned binsize);
	unsigned int get_cpu_id(const std::string& config_file);

	std::string print_cpu_mask(cpu_set_t cpu_mask);
	std::string get_cpu_mask(pid_t pid, cpu_set_t *mask);
	std::string set_cpu_mask(unsigned short cpu_id, cpu_set_t *mask);

	unsigned long long uiui2ull(unsigned int high, unsigned int low);

	int daemon_run();

}




