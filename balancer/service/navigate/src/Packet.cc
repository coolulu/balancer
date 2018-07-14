#include "Packet.h"
#include <cstring>
#include <zlib.h>
#include <muduo/net/Endian.h>
#include "protocol/proto_cpp/version.pb.h"
#include "Define.h"

#include "Log.h"

Packet::Packet(unsigned int header, const char* buffer, unsigned int len)
	:	_buffer(buffer), 
		_data_len(0),
		_header(header),
		_len(len),
		_version(0),
		_from_service_id(0),
		_to_service_id(0),
		_to_proc_id(0),
		_app_id(0),
		_app_version(0),
		_conn_seq_id(0),
		_msg_seq_id(0),
		_data_format(0),
		_reserve_field_0(0),
		_reserve_field_1(0),
		_reserve_field_2(0),
		_reserve_field_3(0),
		_data(nullptr),
		_check_sum(0)
{
	_version			= muduo::net::sockets::networkToHost16(*(unsigned short*)(_buffer + s_version_offset));
	_from_service_id	= muduo::net::sockets::networkToHost16(*(unsigned short*)(_buffer + s_from_service_id_offset));
	_to_service_id		= muduo::net::sockets::networkToHost16(*(unsigned short*)(_buffer + s_to_service_id_offset));
	_to_proc_id			= muduo::net::sockets::networkToHost32(*(unsigned int*)(_buffer + s_to_proc_id_offset));
	_app_id				= muduo::net::sockets::networkToHost32(*(unsigned int*)(_buffer + s_app_id_offset));
	_app_version		= muduo::net::sockets::networkToHost32(*(unsigned int*)(_buffer + s_app_version_offset));
	_conn_seq_id		= muduo::net::sockets::networkToHost64(*(unsigned long long*)(_buffer + s_conn_seq_id_offset));
	_msg_seq_id			= muduo::net::sockets::networkToHost64(*(unsigned long long*)(_buffer + s_msg_seq_id_offset));
	_data_format		= *(unsigned char*)(_buffer + s_data_format_offset);
	_reserve_field_0	= *(unsigned char*)(_buffer + s_reserve_field_0_offset);
	_reserve_field_1	= muduo::net::sockets::networkToHost32(*(unsigned int*)(_buffer + s_reserve_field_1_offset));
	_reserve_field_2	= muduo::net::sockets::networkToHost32(*(unsigned int*)(_buffer + s_reserve_field_2_offset));
	_reserve_field_3	= muduo::net::sockets::networkToHost32(*(unsigned int*)(_buffer + s_reserve_field_3_offset));
	_data				= (unsigned char*)(_buffer + s_data_offset);
	_data_len			= len + s_version_offset - s_data_offset - k_check_sum_size;
	_check_sum			= muduo::net::sockets::networkToHost32(*(unsigned int*)(_buffer + s_data_offset + _data_len));
}

Packet::Packet(unsigned short to_service_id, 
			   unsigned int to_proc_id, 
			   unsigned int app_id, 
			   unsigned int app_version, 
			   unsigned long long conn_seq_id, 
			   unsigned long long msg_seq_id, 
			   unsigned char data_format, 
			   unsigned char reserve_field_0, 
			   unsigned int reserve_field_1, 
			   unsigned int reserve_field_2, 
			   unsigned int reserve_field_3)
	:	_buffer(nullptr),
		_data_len(0),
		_header(0),
		_len(0),
		_version(version::PROTO_VER),
		_from_service_id(Define::service_id),
		_to_service_id(to_service_id),
		_to_proc_id(to_proc_id),
		_app_id(app_id),
		_app_version(app_version),
		_conn_seq_id(conn_seq_id),
		_msg_seq_id(msg_seq_id),
		_data_format(data_format),
		_reserve_field_0(reserve_field_0),
		_reserve_field_1(reserve_field_1),
		_reserve_field_2(reserve_field_2),
		_reserve_field_3(reserve_field_3),
		_data(nullptr),
		_check_sum(0)
{

}

Packet::~Packet()
{
	_buffer = nullptr;	// 不用释放
	_data = nullptr;	// 不用释放
}

bool Packet::check()
{
	unsigned int check_sum = ::adler32(0, reinterpret_cast<const Bytef*>(_buffer + k_header_size), 
									   _len + k_len_size - k_check_sum_size);
	if(check_sum == _check_sum)
	{
		B_LOG_INFO << "check_sum is ok, _msg_seq_id=" << _msg_seq_id << ", check_sum=" << check_sum << ", _check_sum=" << _check_sum;
	}
	else
	{
		B_LOG_ERROR << "check_sum is error, _msg_seq_id=" << _msg_seq_id << ", check_sum=" << check_sum << ", _check_sum=" << _check_sum;
		return false;
	}

	switch (_data_format)
	{
	case data_format::PROTOBUF:
		break;

	case data_format::PROTOBUF_ZIP:
		break;

	case data_format::PROTOBUF_SNAPPY:
		break;

	default:
		B_LOG_ERROR << "_msg_seq_id=" << _msg_seq_id << ", unknow _data_format=" << _data_format;
		return false;
	}

	if(_body.ParseFromArray(_data, _data_len))
	{
		B_LOG_INFO << "_msg_seq_id=" << _msg_seq_id << ", _body.ParseFromArray=true";	
	}
	else
	{
		B_LOG_ERROR << "_msg_seq_id=" << _msg_seq_id << ", _body.ParseFromArray=false";
		return false;
	}

	return true;
}

void Packet::print()
{
	B_LOG_INFO << "_header="			<< _header;
	B_LOG_INFO << "_len="				<< _len;
	B_LOG_INFO << "_version="			<< _version;
	B_LOG_INFO << "_from_service_id="	<< _from_service_id;
	B_LOG_INFO << "_to_service_id="		<< _to_service_id;
	B_LOG_INFO << "_to_proc_id="		<< _to_proc_id;
	B_LOG_INFO << "_app_id="			<< _app_id;
	B_LOG_INFO << "_app_version="		<< _app_version;
	B_LOG_INFO << "_conn_seq_id="		<< _conn_seq_id;
	B_LOG_INFO << "_msg_seq_id="		<< _msg_seq_id;
	B_LOG_INFO << "_data_format="		<< _data_format;
	B_LOG_INFO << "_reserve_field_0="	<< _reserve_field_0;
	B_LOG_INFO << "_reserve_field_1="	<< _reserve_field_1;
	B_LOG_INFO << "_reserve_field_2="	<< _reserve_field_2;
	B_LOG_INFO << "_reserve_field_3="	<< _reserve_field_3;
	B_LOG_INFO << "_check_sum="			<< _check_sum;
	B_LOG_INFO << "_data_len="			<< _data_len;
}


