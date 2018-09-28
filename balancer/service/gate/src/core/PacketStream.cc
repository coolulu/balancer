#include "PacketStream.h"

#include <cstring>

PacketStream::PacketStream(PacketPtr& packet_ptr)
	:	_packet_ptr(packet_ptr),
		_buffer(nullptr),
		_buffer_len(Packet::k_header_size + Packet::k_len_size + packet_ptr->_len)
{
	_buffer = new char[_buffer_len];
	memcpy(_buffer, packet_ptr->_buffer, _buffer_len);
}

PacketStream::~PacketStream()
{
	if(_buffer != nullptr)
	{
		delete [] _buffer;
		_buffer = nullptr;
	}
}
