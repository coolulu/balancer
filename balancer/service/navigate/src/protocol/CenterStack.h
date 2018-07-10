#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/center.pb.h"
#include "Packet.h"

namespace CenterStack
{
	void HeartbeatRsp(data::Body& body, 
					  int level, 
					  int service_id, 
					  unsigned int proc_id,
					  unsigned long long conf_update_time,
					  unsigned int role_expire_time);

};