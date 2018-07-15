#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/center.pb.h"
#include "core/Packet.h"

namespace CenterStack
{
	void HeartbeatReq(data::Body& body, 
					  int level, 
					  int service_id, 
					  unsigned int proc_id,
					  center::HeartbeatReq_State state,
					  unsigned long long conf_update_time,
					  const std::string& conf_json);

};