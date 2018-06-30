#pragma once

#include <string>

namespace util
{
	int get_local_ip(const char *pEthName,int& local_ip);
	const char* bin2hex(const char* buf,int len);
	char char2int(char ch);
	const int hex2bin(const char* hex_str,char* buf,int& len);
	unsigned sip_2_uip(const char* s_ip);
	std::string uip_2_sip(unsigned uip);
	int bin_2_file(const std::string &filepath,const char* ptr,int filelen);
	int file_2_bin(const std::string &filepath,char* ptr, unsigned binsize);
}




