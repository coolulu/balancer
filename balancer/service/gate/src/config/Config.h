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
	static const std::string& gate								= "gate";

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
	static const std::string& gate_server_idle					= "gate_server_idle";
	static const std::string& gate_server_no_delay				= "gate_server_no_delay";
	static const std::string& gate_server_recv_packet_len_max	= "gate_server_recv_packet_len_max";
	static const std::string& gate_server_send_packet_len_max	= "gate_server_send_packet_len_max";
	static const std::string& gate_server_high_water_mark		= "gate_server_high_water_mark";
	static const std::string& wake_heartbeat_timeout_us			= "wake_heartbeat_timeout_us";
	static const std::string& del_session_timeout_us			= "del_session_timeout_us";
	static const std::string& close_client_timeout_us			= "close_client_timeout_us";
	static const std::string& put_load_sync_count				= "put_load_sync_count";
	static const std::string& put_load_sync_gap					= "put_load_sync_gap";
	static const std::string& local_ethernet					= "local_ethernet";
	static const std::string& local_service_id					= "local_service_id";
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
		Listen gate;
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
				gate_server_idle(0), 
				gate_server_no_delay(false),
				gate_server_recv_packet_len_max(0),
				gate_server_send_packet_len_max(0),
				gate_server_high_water_mark(0),
				wake_heartbeat_timeout_us(0),
				del_session_timeout_us(0),
				close_client_timeout_us(0),
				put_load_sync_count(0),
				put_load_sync_gap(0),
				local_service_id(0){}

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

		unsigned short	gate_server_idle;
		bool			gate_server_no_delay;
		unsigned int	gate_server_recv_packet_len_max;
		unsigned int	gate_server_send_packet_len_max;
		unsigned int	gate_server_high_water_mark;
		unsigned int	wake_heartbeat_timeout_us;
		unsigned int	del_session_timeout_us;
		unsigned int	close_client_timeout_us;
		unsigned short	put_load_sync_count;
		unsigned short	put_load_sync_gap;

		std::string		local_ethernet;
		std::string		local_ip;
		unsigned short	local_service_id;
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


