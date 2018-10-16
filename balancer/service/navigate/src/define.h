#pragma once

#include <string>
#include "protocol/protobuf/proto_cpp/service.pb.h"

namespace Define
{
	enum
	{
		BUFFER_SIZE = 1024 * 1024,
	};

	static const std::string& service_version = "0.1.0";

	static unsigned short service_id = 0;	// 赋值区域性service_id,赋值于proc.local_service_id
	static const std::string& service_name = "navigate";

	static const std::string& conf_file_postfix = ".conf";
};