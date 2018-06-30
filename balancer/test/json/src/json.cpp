#include <iostream>
#include <string>
#include <cstdio>

#include "ServiceConfig.h"
#include "util.h"

using namespace std;

#define SERVICE_ID_GATE		11000
#define SERVICE_ID_GROUP	12000
#define SERVICE_ID_PROXY	13000

int main()
{
	string json = "											\
	{														\
        \"service_map\": [                                  \
            {                                               \
				\"service_id\": 11000,                      \
                \"service_name\": \"gate\",                 \
                \"heartbeat\": {                            \
					\"heartbeat_enable\": true,				\
                    \"heartbeat_gap\": 5,                   \
                    \"lose_time\": 3,                       \
                    \"recover_time\": 3                     \
                },                                          \
				\"depend_map\": [                           \
					{                                       \
						\"depend_service_id\": 12000		\
					}                                       \
				],                                          \
                \"kv_map\": [                               \
                    {                                       \
                        \"key\": \"timeout\",               \
                        \"val\": \"30\"                     \
                    },                                      \
                    {                                       \
                        \"key\": \"env\",                   \
                        \"val\": \"test\"                   \
                    }                                       \
                ],                                          \
                \"heartbeat_list\": [                       \
                    {                                       \
						\"proc_id\": 1,						\
                        \"proc_des\": \"gate_001\",         \
                        \"in_ip\": \"121.1.1.1\",           \
                        \"out_ip\": \"11.1.1.1\",           \
                        \"port\": 11001                     \
                    }                                       \
                ],                                          \
                \"inservice_list\": [                       \
                    {                                       \
						\"proc_id\": 2,						\
                        \"proc_des\": \"gate_002\",         \
                        \"in_ip\": \"121.1.1.2\",           \
                        \"out_ip\": \"11.1.1.2\",           \
                        \"port\": 11002                     \
                    }                                       \
                ]                                           \
            },                                              \
            {                                               \
				\"service_id\": 12000,                      \
                \"service_name\": \"group\",                \
                \"heartbeat\": {                            \
					\"heartbeat_enable\": false,			\
                    \"heartbeat_gap\": 5,                   \
                    \"lose_time\": 3,                       \
                    \"recover_time\": 3                     \
                },                                          \
				\"depend_map\": [                           \
					{                                       \
						\"depend_service_id\": 11000		\
					}                                       \
				],                                          \
                \"kv_map\": [                               \
                    {                                       \
                        \"key\": \"name_max_size\",         \
                        \"val\": \"1024\"                   \
                    },                                      \
                    {                                       \
                        \"key\": \"buffer_max_size\",       \
                        \"val\": \"1024\"                   \
                    }                                       \
                ],                                          \
                \"heartbeat_list\": [                       \
                    {                                       \
						\"proc_id\": 1,						\
                        \"proc_des\": \"group_001\",        \
                        \"in_ip\": \"121.1.1.10\",          \
                        \"out_ip\": \"11.1.1.10\",          \
                        \"port\": 11001                     \
                    }                                       \
                ],                                          \
                \"inservice_list\": [                       \
                    {                                       \
						\"proc_id\": 2,						\
                        \"proc_des\": \"group_002\",        \
                        \"in_ip\": \"121.1.1.20\",          \
                        \"out_ip\": \"11.1.1.20\",          \
                        \"port\": 11002                     \
                    }                                       \
                ]                                           \
            }                                               \
        ]                                                   \
    }";

	std::string err;
	ServiceConfig sc;
	bool b;

	if(1)
	{
		util::bin_2_file("config.json", json.c_str(), json.size());

		char buffer[8192] = {0};
		unsigned int buffer_size = sizeof(buffer) / sizeof(char);
		util::file_2_bin("config.json", buffer, buffer_size);
		std::cout << buffer << std::endl;
	}
	
	if(0)
	{
		err = sc.json_to_map(json);
		std::cout << err << std::endl;

		json = sc.map_to_json();
		std::cout << json << std::endl;

		err = sc.json_to_map(json);
		std::cout << err << std::endl;

		json = sc.get_service_list();
		std::cout << json << std::endl;

		json.clear();
		b = sc.get_service_info(SERVICE_ID_GATE, json);
		std::cout << b << std::endl;
		std::cout << json << std::endl;

		ServiceConfig::Heartbeat hb;
		hb.heartbeat_enable = false;
		hb.heartbeat_gap = 1;
		hb.lose_time = 1;
		hb.recover_time = 1;
		b = sc.set_service_heartbeat(SERVICE_ID_GATE, hb);
		std::cout << b << std::endl;

		ServiceConfig::KV kv;
		kv.key = "timeout";
		kv.val = "100";
		b = sc.set_service_kv(SERVICE_ID_GATE, kv);
		std::cout << b << std::endl;

		kv.key = "key";
		kv.val = "val";
		b = sc.add_service_kv(SERVICE_ID_GATE, kv);
		std::cout << b << std::endl;

		b = sc.del_service_kv(SERVICE_ID_GATE, kv.key);
		std::cout << b << std::endl;

		b = sc.del_service_depend(SERVICE_ID_GATE, SERVICE_ID_GROUP);
		std::cout << b << std::endl;

		b = sc.add_service_depend(SERVICE_ID_GATE, SERVICE_ID_GROUP);
		std::cout << b << std::endl;

		ServiceConfig::IPInfo ip_info;
		ip_info.proc_id = 3;
		ip_info.proc_des = "gate_003";
		ip_info.in_ip = "0.0.0.0";
		ip_info.out_ip = "1.1.1.1";
		ip_info.port = 6666;
		b = sc.add_service_heartbeat_list(SERVICE_ID_GATE, ip_info);
		std::cout << b << std::endl;

		b = sc.del_service_heartbeat_list(SERVICE_ID_GATE, ip_info.proc_id);
		std::cout << b << std::endl;

		b = sc.add_service_inservice_list(SERVICE_ID_GATE, 1);
		std::cout << b << std::endl;

		b = sc.del_service_inservice_list(SERVICE_ID_GATE, 1);
		std::cout << b << std::endl;

		hb.heartbeat_enable = true;
		hb.heartbeat_gap = 2;
		hb.lose_time = 2;
		hb.recover_time = 2;
		b = sc.add_service(SERVICE_ID_PROXY, "proxy", hb);
		std::cout << b << std::endl;

		b = sc.del_service(SERVICE_ID_PROXY);
		std::cout << b << std::endl;
	}

	return 0;
}

