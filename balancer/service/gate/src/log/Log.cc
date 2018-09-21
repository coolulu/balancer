#include "Log.h"

#include <muduo/base/Logging.cc>

boost::scoped_ptr<muduo::LogFile> Log::s_logFile;

Log::Log()
{

}

Log::~Log()
{

}

void Log::init(unsigned short log_level, 
			   bool console, 
			   const std::string& file_path,
			   off_t roll_size, 
			   bool thread_safe, 
			   unsigned int flush_interval, 
			   unsigned int check_every_n)
{
	muduo::Logger::setLogLevel((muduo::Logger::LogLevel)log_level);

	if(console)
	{
		muduo::Logger::setOutput(muduo::defaultOutput);
		muduo::Logger::setFlush(muduo::defaultFlush);
	}
	else
	{
		muduo::Logger::setOutput(out_put_func);
		muduo::Logger::setFlush(flush_func);

		s_logFile.reset(new muduo::LogFile(file_path.c_str(), roll_size, thread_safe, 
										   flush_interval, check_every_n));	
	}
}

void Log::out_put_func(const char* msg, int len)
{
	s_logFile->append(msg, len);
}

void Log::flush_func()
{
	s_logFile->flush();
}



