#pragma once

#include <string>

class Define
{
public:
	enum
	{
		BUFFER_SIZE = 1024 * 1024,
	};

	static const std::string& service_version;

	static unsigned short service_id;
	static const std::string& service_name;

	static const std::string& conf_file_postfix;
};