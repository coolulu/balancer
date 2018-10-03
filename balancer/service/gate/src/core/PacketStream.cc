#include "PacketStream.h"

#include <cstring>
#include <zlib.h>
#include <muduo/net/Endian.h>

PacketStream::PacketStream(PacketPtr& packet_ptr)
	:	_packet_ptr(packet_ptr),
		_buffer(new char[packet_ptr->_buffer_len]),
		_buffer_len(packet_ptr->_buffer_len)
{
	memcpy(_buffer, packet_ptr->_buffer, _buffer_len);
}

PacketStream::~PacketStream()
{
	delete [] _buffer;
	_buffer = nullptr;
}

void PacketStream::set_buffer_conn_seq_id(unsigned long long conn_seq_id)
{
	unsigned long long conn_seq_id_be = muduo::net::sockets::hostToNetwork64(conn_seq_id);
	memcpy(_buffer + Packet::s_conn_seq_id_offset, &conn_seq_id_be, sizeof(conn_seq_id_be));
	
	unsigned int check_sum = ::adler32(0, reinterpret_cast<const Bytef*>(_buffer), _buffer_len);
	unsigned int check_sum_be = muduo::net::sockets::hostToNetwork32(check_sum);
	memcpy(_buffer + _buffer_len - sizeof(check_sum_be), &check_sum_be, sizeof(check_sum_be));
}
