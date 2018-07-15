#include "Proc.h"

#include <boost/bind.hpp>
#include "define.h"
#include "tool/Util.h"

bool Proc::s_reload_flag = false;
bool Proc::s_stop_flag = false;

Proc::Proc(muduo::net::EventLoop& loop, const std::string& config_file)
	:	_loop(loop), 
		_config_file(config_file),
		_http_server(*this),
		_timer(*this), 
		_prober(*this),
		_tcp_client_pool(*this)
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

	_log.init(_config.log.level, _config.log.console, _config.log.file_path, _config.log.roll_size,
			  _config.log.thread_safe, _config.log.flush_interval, _config.log.check_every_n);

	char service_json[8192] = {0};
	ret = Util::file_2_bin(_config.proc.service_path, service_json, sizeof(service_json)/sizeof(char));
	if(ret != 0)
	{
		B_LOG_ERROR << "open file proc.service_path=" << _config.proc.service_path;
		return -300;
	}

	err = _sc.json_to_map(service_json);
	if(err.size() > 0)
	{
		B_LOG_ERROR << "service load err=" << err;
		return -400;
	}

	B_LOG_INFO << "sc=" << _sc.map_to_json();

	return 0;
}

void Proc::start()
{
	B_LOG_INFO;
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
