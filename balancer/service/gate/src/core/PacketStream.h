#pragma once

#include <boost/shared_ptr.hpp>
#include "core/Packet.h"

class PacketStream
{
public:
	PacketStream(PacketPtr& packet_ptr);
	~PacketStream();

public:
	PacketPtr		_packet_ptr;
	char*			_buffer;
	unsigned int	_buffer_len;
};

typedef boost::shared_ptr<PacketStream> PacketStreamPtr;