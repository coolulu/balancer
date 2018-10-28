#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/proxy.pb.h"
#include "core/Packet.h"

namespace ProxyStack
{
	void CheckPasswdReq(data::Body& body, unsigned long long user_id, const std::string& passwd);

}