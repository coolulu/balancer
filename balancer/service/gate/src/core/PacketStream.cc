#include "PacketStream.h"

#include <cstring>

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
