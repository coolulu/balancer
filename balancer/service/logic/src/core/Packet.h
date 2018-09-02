#pragma once

#include <boost/shared_ptr.hpp>
#include "protocol/protobuf/proto_cpp/data.pb.h"
#include "protocol/protobuf/proto_cpp/data_format.pb.h"

struct Packet
{
public:
	// 接收数据
	Packet(unsigned int header, const char* buffer, unsigned int len);	

	// 发送数据
	Packet(unsigned short to_service_id,
		   unsigned int to_proc_id,
		   unsigned int app_id, 
		   unsigned int app_version, 
		   unsigned long long conn_seq_id,
		   unsigned long long msg_seq_id, 
		   unsigned char data_format = data_format::PROTOBUF,
		   unsigned char reserve_field_0 = 0, 
		   unsigned int reserve_field_1 = 0, 
		   unsigned int reserve_field_2 = 0, 
		   unsigned int reserve_field_3 = 0);
	~Packet();

public:
	bool check();
	void print();

public:
	const char*					_buffer;			// 从header开始
	unsigned int				_data_len;			// _data的长度

public:
	unsigned int				_header;			// 包头标识
	unsigned int				_len;               // 长度
	unsigned short				_version;           // 协议版本
	unsigned short				_from_service_id;   // 发送的service_id
	unsigned short				_to_service_id;     // 发送到service_id
	unsigned int				_to_proc_id;		// 0为负载均衡，非0则请求到proc_id的服务
	unsigned int				_app_id;         
	unsigned int				_app_version;    
	unsigned long long			_conn_seq_id;       // 客户端连接序列id(用在网关转发)
	unsigned long long			_msg_seq_id;        // 消息序列id
	unsigned char				_data_format;       // 数据格式(1.protobuf)
	unsigned char				_reserve_field_0;   // 保留字段0
	unsigned int				_reserve_field_1;   // 保留字段1
	unsigned int				_reserve_field_2;   // 保留字段2
	unsigned int				_reserve_field_3;   // 保留字段3
	unsigned char*				_data;
	unsigned int				_check_sum;         // 校验和

public:
	data::Body					_body;

public:
	const static unsigned int	k_header			= 0x00000000;
	const static unsigned int	k_header_size		= sizeof(unsigned int);
	const static unsigned int	k_len_size			= sizeof(unsigned int);
	const static unsigned int	k_check_sum_size	= sizeof(unsigned int);

	const static unsigned int	s_header_offset						= 0;
	const static unsigned int	s_len_offset						= 4;
	const static unsigned int	s_version_offset					= 8;
	const static unsigned int	s_from_service_id_offset			= 10;
	const static unsigned int	s_to_service_id_offset				= 12;
	const static unsigned int	s_to_proc_id_offset					= 14;
	const static unsigned int	s_app_id_offset						= 18;
	const static unsigned int	s_app_version_offset				= 22;
	const static unsigned int	s_conn_seq_id_offset				= 26;
	const static unsigned int	s_msg_seq_id_offset					= 34;
	const static unsigned int	s_data_format_offset				= 42;
	const static unsigned int	s_reserve_field_0_offset			= 43;
	const static unsigned int	s_reserve_field_1_offset			= 44;
	const static unsigned int	s_reserve_field_2_offset			= 48;
	const static unsigned int	s_reserve_field_3_offset			= 52;
	const static unsigned int	s_data_offset						= 56;
	const static unsigned int	s_check_sum_no_has_data_len_offset	= 56;	//不包括data_len的偏移

};


typedef boost::shared_ptr<Packet> PacketPtr;