#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/navigate.pb.h"
#include "core/Packet.h"

namespace NavigateStack
{
	void PutLoadReq(data::Body& body, 
					int service_id, 
					unsigned int proc_id, 
					int load_val);
}