#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/session.pb.h"
#include "core/Packet.h"

namespace SessionStack
{
	void QuerySessionReq(data::Body& body, unsigned long long user_id);

	void DelSessionReq(data::Body& body,
					   unsigned long long user_id,
					   const std::string& in_ip,
					   int in_port,
					   unsigned int conn_id);

	void CreateSessionReq(data::Body& body,
						  unsigned long long user_id,
						  int service_id,
						  unsigned int proc_id,
						  const std::string& in_ip,
						  int in_port,
						  unsigned long long conn_id,
						  unsigned int create_time,
						  int version,
						  unsigned int app_id,
						  unsigned int app_version,
						  unsigned int dev_type);

}