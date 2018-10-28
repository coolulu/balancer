#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/center.pb.h"
#include "core/Packet.h"

namespace CenterStack
{
	void HeartbeatRsp(data::Body& body,
					  int code,
					  const std::string& info,
					  int level, 
					  int service_id, 
					  unsigned int proc_id,
					  unsigned long long conf_update_time,
					  unsigned int expire_second);

}