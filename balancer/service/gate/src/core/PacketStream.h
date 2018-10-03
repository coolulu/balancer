#pragma once

#include <boost/shared_ptr.hpp>
#include "core/Packet.h"

// PacketPtr�е�bufferҪ�ӳ�ʹ�ã���Ҫ����һ��ʱʹ��
// PacketPtr�е�bufferָ��ֻ�ڵ�һ�δ�������ʱ�ǿɿ���
class PacketStream
{
public:
	PacketStream(PacketPtr& packet_ptr);
	~PacketStream();

public:
	void set_buffer_conn_seq_id(unsigned long long conn_seq_id);

public:
	PacketPtr		_packet_ptr;
	char*			_buffer;
	unsigned int	_buffer_len;
};

typedef boost::shared_ptr<PacketStream> PacketStreamPtr;