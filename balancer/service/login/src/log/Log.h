#pragma once

#include <string>
#include <muduo/base/LogFile.h>
#include <muduo/base/Logging.h>

class Log
{
public:
	Log();
	~Log();

public:
	void init(unsigned short log_level,
			  bool console,
			  const std::string& file_path,
			  off_t roll_size, 
			  bool thread_safe,
			  unsigned int flush_interval,
			  unsigned int check_every_n);

private:
	static void out_put_func(const char* msg, int len);
	static void flush_func();

private:
	static boost::scoped_ptr<muduo::LogFile> s_logFile;

};

#define B_LOG_TRACE LOG_TRACE << "[" << __FUNCTION__ << "] "
#define B_LOG_DEBUG LOG_DEBUG << "[" << __FUNCTION__ << "] "
#define B_LOG_INFO  LOG_INFO  << "[" << __FUNCTION__ << "] "
#define B_LOG_WARN  LOG_WARN  << "[" << __FUNCTION__ << "] "
#define B_LOG_ERROR LOG_ERROR << "[" << __FUNCTION__ << "] "
#define B_LOG_FATAL LOG_FATAL << "[" << __FUNCTION__ << "] "
