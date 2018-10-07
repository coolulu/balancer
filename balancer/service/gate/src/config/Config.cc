#include "Config.h"

#include "tool/Util.h"

std::string Config::load(const std::string& json)
{
	rapidjson::Document document;
	document.Parse(json.c_str());
	if(!document.IsObject())
		return err_is_not_object(json);

	{
		if(!document.HasMember(KeyConfig::net.c_str()))
			return err_is_not_object(KeyConfig::net);
		const rapidjson::Value& cv = document[KeyConfig::net.c_str()];
		if(!cv.IsObject())
			return err_is_not_object(KeyConfig::net);

		{
			const rapidjson::Value& cv_tcp = cv[KeyConfig::tcp.c_str()];
			if(!cv_tcp.IsObject())
				return err_is_not_object(KeyConfig::tcp);
			if(!get_string(cv_tcp, KeyConfig::ip, net.tcp.ip))
				return err_is_not_string(KeyConfig::ip);
			if(!get_uint(cv_tcp, KeyConfig::port, net.tcp.port))
				return err_is_not_uint(KeyConfig::port);

			const rapidjson::Value& cv_http = cv[KeyConfig::http.c_str()];
			if(!cv_http.IsObject())
				return err_is_not_object(KeyConfig::http);
			if(!get_string(cv_http, KeyConfig::ip, net.http.ip))
				return err_is_not_string(KeyConfig::ip);
			if(!get_uint(cv_http, KeyConfig::port, net.http.port))
				return err_is_not_uint(KeyConfig::port);

			const rapidjson::Value& cv_gate = cv[KeyConfig::gate.c_str()];
			if(!cv_gate.IsObject())
				return err_is_not_object(KeyConfig::gate);
			if(!get_string(cv_gate, KeyConfig::ip, net.gate.ip))
				return err_is_not_string(KeyConfig::ip);
			if(!get_uint(cv_gate, KeyConfig::port, net.gate.port))
				return err_is_not_uint(KeyConfig::port);
		}	
	}
	
	{
		if(!document.HasMember(KeyConfig::log.c_str()))
			return err_is_not_object(KeyConfig::log);
		const rapidjson::Value& cv = document[KeyConfig::log.c_str()];
		if(!cv.IsObject())
			return err_is_not_object(KeyConfig::log);

		if(!get_uint_maybe_0(cv, KeyConfig::level, log.level))
			return err_is_not_uint(KeyConfig::level);
		if(!get_bool(cv, KeyConfig::console, log.console))
			return err_is_not_bool(KeyConfig::console);	
		if(!get_string(cv, KeyConfig::file_path, log.file_path))
			return err_is_not_string(KeyConfig::file_path);
		if(!get_uint(cv, KeyConfig::roll_size, log.roll_size))
			return err_is_not_uint(KeyConfig::roll_size);	
		if(!get_bool(cv, KeyConfig::thread_safe, log.thread_safe))
			return err_is_not_bool(KeyConfig::thread_safe);	
		if(!get_uint_maybe_0(cv, KeyConfig::flush_interval, log.flush_interval))
			return err_is_not_uint(KeyConfig::flush_interval);	
		if(!get_uint_maybe_0(cv, KeyConfig::check_every_n, log.check_every_n))
			return err_is_not_uint(KeyConfig::check_every_n);	
	}

	{
		if(!document.HasMember(KeyConfig::proc.c_str()))
			return err_is_not_object(KeyConfig::proc);
		const rapidjson::Value& cv = document[KeyConfig::proc.c_str()];
		if(!cv.IsObject())
			return err_is_not_object(KeyConfig::proc);

		if(!get_uint(cv, KeyConfig::tcp_server_idle, proc.tcp_server_idle))
			return err_is_not_uint(KeyConfig::tcp_server_idle);
		if(!get_bool(cv, KeyConfig::tcp_server_no_delay, proc.tcp_server_no_delay))
			return err_is_not_bool(KeyConfig::tcp_server_no_delay);	
		if(!get_uint(cv, KeyConfig::tcp_server_recv_packet_len_max, proc.tcp_server_recv_packet_len_max))
			return err_is_not_uint(KeyConfig::tcp_server_recv_packet_len_max);
		if(!get_uint(cv, KeyConfig::tcp_server_send_packet_len_max, proc.tcp_server_send_packet_len_max))
			return err_is_not_uint(KeyConfig::tcp_server_send_packet_len_max);
		if(!get_uint(cv, KeyConfig::tcp_server_high_water_mark, proc.tcp_server_high_water_mark))
			return err_is_not_uint(KeyConfig::tcp_server_high_water_mark);

		if(!get_uint(cv, KeyConfig::tcp_client_idle, proc.tcp_client_idle))
			return err_is_not_uint(KeyConfig::tcp_client_idle);
		if(!get_bool(cv, KeyConfig::tcp_client_no_delay, proc.tcp_client_no_delay))
			return err_is_not_bool(KeyConfig::tcp_client_no_delay);		
		if(!get_uint(cv, KeyConfig::tcp_client_recv_packet_len_max, proc.tcp_client_recv_packet_len_max))
			return err_is_not_uint(KeyConfig::tcp_client_recv_packet_len_max);		
		if(!get_uint(cv, KeyConfig::tcp_client_send_packet_len_max, proc.tcp_client_send_packet_len_max))
			return err_is_not_uint(KeyConfig::tcp_client_send_packet_len_max);
		if(!get_uint(cv, KeyConfig::tcp_client_high_water_mark, proc.tcp_client_high_water_mark))
			return err_is_not_uint(KeyConfig::tcp_client_high_water_mark);
		if(!get_uint(cv, KeyConfig::tcp_client_msg_reduce_size, proc.tcp_client_msg_reduce_size))
			return err_is_not_uint(KeyConfig::tcp_client_msg_reduce_size);

		if(!get_uint(cv, KeyConfig::gate_server_idle, proc.gate_server_idle))
			return err_is_not_uint(KeyConfig::gate_server_idle);
		if(!get_bool(cv, KeyConfig::gate_server_no_delay, proc.gate_server_no_delay))
			return err_is_not_bool(KeyConfig::gate_server_no_delay);	
		if(!get_uint(cv, KeyConfig::gate_server_recv_packet_len_max, proc.gate_server_recv_packet_len_max))
			return err_is_not_uint(KeyConfig::gate_server_recv_packet_len_max);
		if(!get_uint(cv, KeyConfig::gate_server_send_packet_len_max, proc.gate_server_send_packet_len_max))
			return err_is_not_uint(KeyConfig::gate_server_send_packet_len_max);
		if(!get_uint(cv, KeyConfig::gate_server_high_water_mark, proc.gate_server_high_water_mark))
			return err_is_not_uint(KeyConfig::gate_server_high_water_mark);
		if(!get_uint(cv, KeyConfig::wake_heartbeat_timeout_us, proc.wake_heartbeat_timeout_us))
			return err_is_not_uint(KeyConfig::wake_heartbeat_timeout_us);
		if(!get_uint(cv, KeyConfig::del_session_timeout_us, proc.del_session_timeout_us))
			return err_is_not_uint(KeyConfig::del_session_timeout_us);

		if(!get_string(cv, KeyConfig::local_ethernet, proc.local_ethernet))
			return err_is_not_uint(KeyConfig::local_ethernet);
		unsigned int ip = Util::get_ethernet_ip(proc.local_ethernet.c_str());
		if(ip == 0)
			return "ip is 0";
		proc.local_ip = Util::uip_2_sip(ip);
	}

	return "";
}

std::string Config::reload(const std::string& json)
{
	Config config;
	std::string err = config.load(json);
	if(err.empty())
	{
		log = config.log;
		proc = config.proc;
	}

	return err;
}

bool Config::get_string(const rapidjson::Value& v, const std::string& key, std::string& str)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsString())
		{
			str = tmp.GetString();
			return str.size() > 0;
		}
	}

	return false;
}

bool Config::get_uint(const rapidjson::Value& v, const std::string& key, unsigned short& i)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsUint())
		{
			i = tmp.GetUint();
			return i != 0;
		}
	}

	return false;
}

bool Config::get_uint_maybe_0(const rapidjson::Value& v, const std::string& key, unsigned short& i)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsUint())
		{
			i = tmp.GetUint();
			return true;
		}
	}

	return false;
}

bool Config::get_uint(const rapidjson::Value& v, const std::string& key, unsigned int& i)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsUint())
		{
			i = tmp.GetUint();
			return i != 0;
		}
	}

	return false;
}

bool Config::get_uint_maybe_0(const rapidjson::Value& v, const std::string& key, unsigned int& i)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsUint())
		{
			i = tmp.GetUint();
			return true;
		}
	}

	return false;
}

bool Config::get_bool(const rapidjson::Value& v, const std::string& key, bool& b)
{
	if(v.HasMember(key.c_str()))
	{
		const rapidjson::Value& tmp = v[key.c_str()];
		if(tmp.IsBool())
		{
			b = tmp.GetBool();
			return true;
		}
	}

	return false;
}

std::string Config::to_string()
{
	return	"Config.to_string"
			", net.tcp.ip="								+ net.tcp.ip + 
			", net.tcp.port="							+ std::to_string(net.tcp.port) + 
			", net.http.ip="							+ net.http.ip + 
			", net.http.port="							+ std::to_string(net.http.port) + 
			", net.gate.ip="							+ net.gate.ip + 
			", net.gate.port="							+ std::to_string(net.gate.port) + 
			", log.level="								+ std::to_string(log.level) + 
			", log.console="							+ (log.console ? "true" : "false") + 
			", log.file_path="							+ log.file_path + 
			", log.roll_size="							+ std::to_string(log.roll_size) + 
			", log.thread_safe="						+ (log.thread_safe ? "true" : "false") + 
			", log.flush_interval="						+ std::to_string(log.flush_interval) + 
			", log.check_every_n="						+ std::to_string(log.check_every_n) + 
			", proc.tcp_server_idle="					+ std::to_string(proc.tcp_server_idle) + 
			", proc.tcp_server_no_delay="				+ (proc.tcp_server_no_delay ? "true" : "false") + 
			", proc.tcp_server_recv_packet_len_max="	+ std::to_string(proc.tcp_server_recv_packet_len_max) + 
			", proc.tcp_server_send_packet_len_max="	+ std::to_string(proc.tcp_server_send_packet_len_max) + 
			", proc.tcp_server_high_water_mark="		+ std::to_string(proc.tcp_server_high_water_mark) + 
			", proc.tcp_client_idle="					+ std::to_string(proc.tcp_client_idle) + 		
			", proc.tcp_client_no_delay="				+ (proc.tcp_client_no_delay ? "true" : "false") + 		
			", proc.tcp_client_recv_packet_len_max="	+ std::to_string(proc.tcp_client_recv_packet_len_max) + 
			", proc.tcp_client_send_packet_len_max="	+ std::to_string(proc.tcp_client_send_packet_len_max) + 
			", proc.tcp_client_high_water_mark="		+ std::to_string(proc.tcp_client_high_water_mark) + 
			", proc.tcp_client_msg_reduce_size="		+ std::to_string(proc.tcp_client_msg_reduce_size) +
			", proc.gate_server_idle="					+ std::to_string(proc.gate_server_idle) + 
			", proc.gate_server_no_delay="				+ (proc.gate_server_no_delay ? "true" : "false") + 
			", proc.gate_server_recv_packet_len_max="	+ std::to_string(proc.gate_server_recv_packet_len_max) + 
			", proc.gate_server_send_packet_len_max="	+ std::to_string(proc.gate_server_send_packet_len_max) + 
			", proc.gate_server_high_water_mark="		+ std::to_string(proc.gate_server_high_water_mark) +
			", proc.wake_heartbeat_timeout_us="			+ std::to_string(proc.wake_heartbeat_timeout_us) +
			", proc.del_session_timeout_us="			+ std::to_string(proc.del_session_timeout_us) +
			", proc.local_ethernet="					+ proc.local_ethernet + 
			", proc.local_ip="							+ proc.local_ip;
}




