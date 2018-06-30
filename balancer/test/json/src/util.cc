#include "util.h"

#include <cstdio>
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

int util::get_local_ip(const char *pEthName,int& local_ip)
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

const char* util::bin2hex(const char* buf,int len)
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

char util::char2int(char ch)
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

const int util::hex2bin(const char* hex_str,char* buf,int& len)
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

unsigned util::sip_2_uip(const char* s_ip)
{
        struct in_addr addr;
        inet_aton(s_ip,&addr);
        return addr.s_addr;
}

std::string util::uip_2_sip(unsigned uip)
{
	std::string s_ip;
	struct in_addr addr;
	addr.s_addr = uip;
	s_ip = inet_ntoa(addr);
	return s_ip;
}

int util::bin_2_file(const std::string &filepath,const char* ptr,int filelen)
{
    std::string tmp_file = filepath + ".tmp";
    std::fstream outfile(tmp_file.c_str(), std::ios::binary|std::ios::out);
    outfile.write(ptr,filelen);
    outfile.close();

    rename(tmp_file.c_str(), filepath.c_str());
    return 0;
}

int util::file_2_bin(const std::string &filepath,char* ptr, unsigned binsize)
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