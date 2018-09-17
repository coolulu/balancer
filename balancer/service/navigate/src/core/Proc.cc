#include "Proc.h"

#include <boost/bind.hpp>
#include "define.h"
#include "tool/Util.h"

bool Proc::s_reload_flag = false;
bool Proc::s_stop_flag = false;

Proc::Proc(muduo::net::EventLoop& loop,
		   const std::string& config_file,
		   const unsigned int conf_id)
	:	_loop(loop), 
		_config_file(config_file),
		_conf_id(conf_id),
		_tcp_server(*this),
		_http_server(*this),
		_timer(*this)
{

}

Proc::~Proc()
{

}

int Proc::init()
{
	int ret = 0;
	std::string err;

	char config_json[Define::BUFFER_SIZE] = {0};
	ret = Util::file_2_bin(_config_file, config_json, sizeof(config_json)/sizeof(char));
	if(ret != 0)
	{
		B_LOG_ERROR << "open file config_file=" << _config_file;
		return -100;
	}

	err = _config.load(config_json);
	if(err.size() > 0)
	{
		B_LOG_ERROR << "config load err=" << err;
		return -200;
	}

	B_LOG_INFO << _config.to_string();
	return 0;
}

void Proc::start()
{
	B_LOG_INFO;
	_tcp_server.start();
	_http_server.start();
	_loop.runEvery(0.1, boost::bind(&Timer::check_timeout, &_timer));
}

void Proc::quit()
{
	B_LOG_INFO;
	_loop.quit();
}

void Proc::loop()
{
	B_LOG_INFO;
	_loop.loop();
}

void Proc::logging()
{
	_log.init(_config.log.level, _config.log.console, _config.log.file_path, _config.log.roll_size,
			  _config.log.thread_safe, _config.log.flush_interval, _config.log.check_every_n);
}

void Proc::check_flag()
{
	if(s_reload_flag)
	{
		s_reload_flag = false;
		B_LOG_ERROR << "reload start";

		if(reload())
		{
			B_LOG_ERROR << "reload end";
			logging();
		}
		else
		{
			B_LOG_ERROR << "reload failed";
		}	
	}

	if(s_stop_flag)
	{
		s_stop_flag = false;
		B_LOG_ERROR << "stop start";
		quit();
	}
}

bool Proc::reload()
{
	// 有错误，则不重新加载
	int ret = 0;
	std::string err;

	char config_json[Define::BUFFER_SIZE] = {0};
	ret = Util::file_2_bin(_config_file, config_json, sizeof(config_json)/sizeof(char));
	if(ret != 0)
	{
		B_LOG_ERROR << "open file config_file=" << _config_file;
		return false;
	}

	err = _config.reload(config_json);
	if(err.size() > 0)
	{
		B_LOG_ERROR << "config load err=" << err;
		return false;
	}

	B_LOG_INFO << _config.to_string();
	return true;
}


