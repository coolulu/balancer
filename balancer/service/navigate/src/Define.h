#pragma once

#include <string>
#include "protocol/proto_cpp/service.pb.h"

namespace Define
{
	enum
	{
		BUFFER_SIZE = 1024 * 1024,
	};

	static const std::string& service_version = "0.1.0";

	static const unsigned short service_id = service::NAVIGATE;
	static const std::string& service_name = "navigate";
};