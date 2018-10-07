#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/session.pb.h"
#include "core/Packet.h"

namespace SessionStack
{
	void DelSessionReq(data::Body& body,
					   unsigned long long user_id,
					   const std::string& in_ip,
					   int in_port,
					   unsigned int conn_id);
};