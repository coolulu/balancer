#include "Util.h"

#include <cstdio>
#include <cstdlib>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <linux/kernel.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sched.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h> 

int Util::get_local_ip(const char *pEthName,int& local_ip)
{
    struct ifreq req;
    int sock_fd;
    strncpy (req.ifr_name, pEthName, IFNAMSIZ);
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
        printf("get_local_ip: socket error!\r\n");
        return -1;
    }
 
    if (ioctl(sock_fd, SIOCGIFADDR, (char *)&req) < 0)
    {
        printf("get_local_ip: ioctl error!\r\n");
        close(sock_fd);
        return -1;
    }
	local_ip = (((struct sockaddr_in*)(&req.ifr_addr))->sin_addr).s_addr;
    close(sock_fd);
	return 0;
}

const char* Util::bin2hex(const char* buf,int len)
{
   static char temp[10240];
   char table[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
   
   memset(temp,0,sizeof(temp));
   for(int n=0;n<len;++n)
   {
      char ch=buf[n];
      temp[n*2+1]   = table[ch&0x0f];
      temp[n*2] = table[(ch&0xf0)>>4];
   }

   return temp;	
}

char Util::char2int(char ch)
{
   if(ch>='0' && ch<='9')
   {
      return ch-'0';
   }

   if(ch>='a' && ch<='f')
   {
      return ch-'a'+10;
   }

   if(ch>='A' && ch<='F')
   {
      return ch-'A'+10;
   }

   //error character
   return 0;
}

const int Util::hex2bin(const char* hex_str,char* buf,int& len)
{
   int hex_len=strlen(hex_str);
   if(len < hex_len/2)
   {
      return hex_len/2;
   }

   len = hex_len/2;
  
   const char* p=hex_str;
   for(int n=0;n<hex_len;n+=2)
   {
      char ch=0;
      ch = char2int(p[n+1]);
      ch+= char2int(p[n])<<4;

      buf[n/2]=ch;
   }

   return 0;
}

unsigned int get_ethernet_ip(const char* ethernet_name)
{
	struct ifreq req;
	int sock_fd;
	strncpy (req.ifr_name, ethernet_name, IFNAMSIZ);
	if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		return 0;
	}

	if (ioctl(sock_fd, SIOCGIFADDR, (char *)&req) < 0)
	{
		close(sock_fd);
		return 0;
	}

	close(sock_fd);
	unsigned int ip = (((struct sockaddr_in*)(&req.ifr_addr))->sin_addr).s_addr;
	return ip;
}

unsigned int Util::sip_2_uip(const char* sip)
{
        struct in_addr addr;
        inet_aton(sip,&addr);
        return addr.s_addr;
}

std::string Util::uip_2_sip(unsigned uip)
{
	std::string sip;
	struct in_addr addr;
	addr.s_addr = uip;
	sip = inet_ntoa(addr);
	return sip;
}

int Util::bin_2_file(const std::string &filepath,const char* ptr,int filelen)
{
    std::string tmp_file = filepath + ".tmp";
    std::fstream outfile(tmp_file.c_str(), std::ios::binary|std::ios::out);
    outfile.write(ptr,filelen);
    outfile.close();

    rename(tmp_file.c_str(), filepath.c_str());
    return 0;
}

int Util::file_2_bin(const std::string &filepath,char* ptr, unsigned binsize)
{
    FILE* fp=fopen(filepath.c_str(),"rb");
    if(fp==NULL)
    {
        return -1;
    }
    fseek(fp,SEEK_SET,SEEK_END);
    unsigned size=ftell(fp);
	fclose(fp);

    if (binsize < size)
    {
        return -2;
    }
    std::fstream infile(filepath.c_str(), std::ios::binary|std::ios::in);
    infile.read(ptr,size);
    infile.close();
    return 0;
}

unsigned int Util::get_conf_id(const std::string& config_file)
{
	std::string basename = ::basename(config_file.c_str());
	auto begin = basename.find("_");
	auto end = basename.find(".json");
	if(begin != std::string::npos && end != std::string::npos && begin + 1 < end)
	{
		return atoi(basename.substr(begin + 1, end).c_str());
	}

	return 0;
}


std::string Util::print_cpu_mask(cpu_set_t cpu_mask)
{
	std::string str = "cpu affinity is ";
	unsigned char flag = 0;
	
	for (unsigned int i = 0; i < sizeof(cpu_set_t); i ++)
	{
		if (CPU_ISSET(i, &cpu_mask))
		{
			if (flag == 0)
			{
				flag = 1;
				str += std::to_string(i) + " ";
			}
			else
			{
				str += std::to_string(i) + " ";
			}
		}
	}
	
	return str;
}

std::string Util::get_cpu_mask(pid_t pid, cpu_set_t *mask)
{
	if(sched_getaffinity(pid, sizeof(cpu_set_t), mask) == -1)
	{
		return std::string("get cpu affinity failed, ") + strerror(errno);
	}

	return "";
}

std::string Util::set_cpu_mask(unsigned short cpu_id, cpu_set_t *mask)
{
	CPU_ZERO(mask);
	CPU_SET(cpu_id, mask);
	if (sched_setaffinity(0, sizeof(cpu_set_t), mask) == -1)
	{
		return std::string("set cpu affinity failed, ") + strerror(errno);
	}

	return "";
}

unsigned long long Util::uiui2ull(unsigned int high, unsigned int low)
{
	unsigned long long ull = 0;
	memcpy((char*)&ull, (char*)&low, sizeof(low));
	memcpy((char*)&ull + sizeof(low), (char*)&high, sizeof(high));
	return ull;
}

int Util::daemon_run()
{
	::signal(SIGCHLD, SIG_IGN);
	//1）在父进程中，fork返回新创建子进程的进程ID；
	//2）在子进程中，fork返回0；
	//3）如果出现错误，fork返回一个负值；
	int pid = ::fork();
	if (pid < 0)
	{
		return -1;
	}
	else if (pid > 0) 
	{
		::exit(0);	//父进程退出，子进程独立运行
	}
	//之前parent和child运行在同一个session里,parent是会话（session）的领头进程,
	//parent进程作为会话的领头进程，如果exit结束执行的话，那么子进程会成为孤儿进程，并被init收养。
	//执行setsid()之后,child将重新获得一个新的会话(session)id。
	//这时parent退出之后,将不会影响到child了。
	::setsid();
	int fd;
	fd = ::open("/dev/null", O_RDWR, 0);
	if (fd != -1)
	{
		::dup2(fd, STDIN_FILENO);
		::dup2(fd, STDOUT_FILENO);
		::dup2(fd, STDERR_FILENO);
	}

	if (fd > 2)
	{
		::close(fd);
	}

	return 0;

	//daemon(0, 0);
}

short Util::str_2_short(const std::string& str)
{
	std::istringstream is(str);
	short i;
	is >> i;
	return i;
}

unsigned short Util::str_2_ushort(const std::string& str)
{
	std::istringstream is(str);
	unsigned short i;
	is >> i;
	return i;
}

int Util::str_2_int(const std::string& str)
{
	std::istringstream is(str);
	int i;
	is >> i;
	return i;
}

unsigned int Util::str_2_uint(const std::string& str)
{
	std::istringstream is(str);
	unsigned int i;
	is >> i;
	return i;
}

unsigned long long Util::get_us()
{
	struct timeval tv; 
	::gettimeofday(&tv, NULL);  
	return tv.tv_sec * 1000000 + tv.tv_usec;

}
