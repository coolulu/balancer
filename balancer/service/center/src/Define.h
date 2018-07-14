#pragma once

#include <string>

namespace Define
{
	enum
	{
		BUFFER_SIZE = 1024 * 1024,
	};

	static const std::string& service_version = "0.1.0";

	static const unsigned short service_id = 10100;
	static const std::string& service_name = "center";
};