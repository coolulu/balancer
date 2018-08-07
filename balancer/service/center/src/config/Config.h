#pragma once

#include <string>
#include <rapidjson/document.h>

namespace KeyConfig
{
	static const std::string& net								= "net";
	static const std::string& tcp								= "tcp";
	static const std::string& ip								= "ip";
	static const std::string& port								= "port";
	static const std::string& http								= "http";

	static const std::string& log								= "log";
	static const std::string& level								= "level";
	static const std::string& console							= "console";
	static const std::string& file_path							= "file_path";
	static const std::string& roll_size							= "roll_size";
	static const std::string& thread_safe						= "thread_safe";
	static const std::string& flush_interval					= "flush_interval";
	static const std::string& check_every_n						= "check_every_n";

	static const std::string& proc								= "proc";
	static const std::string& tcp_server_idle					= "tcp_server_idle";
	static const std::string& tcp_server_no_delay				= "tcp_server_no_delay";
	static const std::string& tcp_server_recv_packet_len_max	= "tcp_server_recv_packet_len_max";
	static const std::string& tcp_server_send_packet_len_max	= "tcp_server_send_packet_len_max";
	static const std::string& tcp_server_high_water_mark		= "tcp_server_high_water_mark";
	static const std::string& tcp_client_idle					= "tcp_client_idle";
	static const std::string& tcp_client_no_delay				= "tcp_client_no_delay";
	static const std::string& tcp_client_recv_packet_len_max	= "tcp_client_recv_packet_len_max";
	static const std::string& tcp_client_send_packet_len_max	= "tcp_client_send_packet_len_max";
	static const std::string& tcp_client_high_water_mark		= "tcp_client_high_water_mark";
	static const std::string& tcp_client_msg_reduce_size		= "tcp_client_msg_reduce_size";
	static const std::string& level_expire_time					= "level_expire_time";
	static const std::string& service_path						= "service_path";
	static const std::string& prober_timeout_us					= "prober_timeout_us";
}

class Config
{
public:
	struct Listen
	{
		Listen(): port(0){}

		std::string		ip;
		unsigned short	port;
	};
	
	struct Net
	{
		Net(){}

		Listen tcp;
		Listen http;
	};

	struct Log
	{
		Log(): level(0), console(false), roll_size(0), thread_safe(false), flush_interval(0), check_every_n(0){}

		unsigned short	level;
		bool			console;
		std::string		file_path;
		unsigned int	roll_size;
		bool			thread_safe;
		unsigned int	flush_interval;
		unsigned int	check_every_n;
	};

	struct Proc
	{
		Proc(): tcp_server_idle(0), 
				tcp_server_no_delay(false),
				tcp_server_recv_packet_len_max(0),
				tcp_server_send_packet_len_max(0),
				tcp_server_high_water_mark(0),
				tcp_client_idle(0), 
				tcp_client_no_delay(false),
				tcp_client_recv_packet_len_max(0),
				tcp_client_send_packet_len_max(0),
				tcp_client_high_water_mark(0),
				tcp_client_msg_reduce_size(0), 		
				level(0),
				level_expire_time(0),
				prober_timeout_us(0){}

		unsigned short	tcp_server_idle;
		bool			tcp_server_no_delay;
		unsigned int	tcp_server_recv_packet_len_max;
		unsigned int	tcp_server_send_packet_len_max;
		unsigned int	tcp_server_high_water_mark;

		unsigned short	tcp_client_idle;	
		bool			tcp_client_no_delay;		
		unsigned int	tcp_client_recv_packet_len_max;		
		unsigned int	tcp_client_send_packet_len_max;		
		unsigned int	tcp_client_high_water_mark;
		unsigned short	tcp_client_msg_reduce_size;

		unsigned short	level;
		unsigned int	level_expire_time;
		std::string		service_path;
		unsigned int	prober_timeout_us;
	};

public:
	Config(){}
	~Config(){}

public:
	std::string load(const std::string& json);
	std::string reload(const std::string& json);
	std::string to_string();

private:
	bool get_string(const rapidjson::Value& v, const std::string& key, std::string& str);
	bool get_uint(const rapidjson::Value& v, const std::string& key, unsigned short& i);
	bool get_uint_maybe_0(const rapidjson::Value& v, const std::string& key, unsigned short& i);
	bool get_uint(const rapidjson::Value& v, const std::string& key, unsigned int& i);
	bool get_uint_maybe_0(const rapidjson::Value& v, const std::string& key, unsigned int& i);
	bool get_bool(const rapidjson::Value& v, const std::string& key, bool& b);

	inline std::string err_is_not_object(const std::string& key)	{return key + " is not object";}
	inline std::string err_is_not_string(const std::string& key)	{return key + " is not string";}
	inline std::string err_is_not_uint(const std::string& key)		{return key + " is not uint";}
	inline std::string err_is_not_bool(const std::string& key)		{return key + " is not bool";}

public:
	Net		net;
	Log		log;
	Proc	proc;
};


