#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/login.pb.h"
#include "core/Packet.h"

namespace LoginStack
{
	void LoginRsp(data::Body& body, int code, const std::string& info);

	void AccessKeyReq(data::Body& body);

}