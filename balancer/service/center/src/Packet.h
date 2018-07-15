#pragma once

#include <boost/shared_ptr.hpp>
#include "protocol/protobuf/proto_cpp/data.pb.h"
#include "protocol/protobuf/proto_cpp/data_format.pb.h"

struct Packet
{
public:
	// ��������
	Packet(unsigned int header, const char* buffer, unsigned int len);	

	// ��������
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
	const char*					_buffer;			// ��header��ʼ
	unsigned int				_data_len;			// _data�ĳ���

public:
	unsigned int				_header;			// ��ͷ��ʶ
	unsigned int				_len;               // ����
	unsigned short				_version;           // Э��汾
	unsigned short				_from_service_id;   // ���͵�service_id
	unsigned short				_to_service_id;     // ���͵�service_id
	unsigned int				_to_proc_id;		// 0Ϊ���ؾ��⣬��0������proc_id�ķ���
	unsigned int				_app_id;         
	unsigned int				_app_version;    
	unsigned long long			_conn_seq_id;       // �ͻ�����������id(��������ת��)
	unsigned long long			_msg_seq_id;        // ��Ϣ����id
	unsigned char				_data_format;       // ���ݸ�ʽ(1.protobuf)
	unsigned char				_reserve_field_0;   // �����ֶ�0
	unsigned int				_reserve_field_1;   // �����ֶ�1
	unsigned int				_reserve_field_2;   // �����ֶ�2
	unsigned int				_reserve_field_3;   // �����ֶ�3
	unsigned char*				_data;
	unsigned int				_check_sum;         // У���

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
	const static unsigned int	s_check_sum_no_has_data_len_offset	= 56;	//������data_len��ƫ��

};


typedef boost::shared_ptr<Packet> PacketPtr;