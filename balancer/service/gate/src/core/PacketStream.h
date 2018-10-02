#pragma once

#include <boost/shared_ptr.hpp>
#include "core/Packet.h"

// PacketPtr中的buffer要延迟使用，需要复制一份时使用
// PacketPtr中的buffer指针只在第一次触发唤醒时是可靠的
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