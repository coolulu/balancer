#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/gate.pb.h"
#include "core/Packet.h"

namespace GateStack
{
	void GetConnIdRsp(data::Body& body,
					  int code,
					  const std::string& info,
					  unsigned long long server_time,
					  unsigned int conn_create_time,
					  unsigned long long conn_id);
};