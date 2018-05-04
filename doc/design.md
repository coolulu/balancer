# balancer

# 目录
[toc]

## 消息设计
### 数据包格式
    HLV格式
    struct Packet
    {
        unsigned short 		head			:2
        unsigned short		len				:2
        unsigned short		version			:2
        unsigned short 		service_id		:2
        unsigned int 		app_id			:4
        unsigned int 		session_id		:4
        unsigned char		data[]			:len
        unsigned int		crc				:4
    }
    head = [0x00,0x00]
    len = len(version + service_id + app_id + session_id + data[] + crc)
    len(message) = 20 + len(data[])

### Proto
    message Message
    {
        repeated uint64    timestamp 		= 1;
        optional uint32    error_code  		= 2;	//rsp必填
        optional bytes     error_info   	= 3;	//rsp必填
        extensions 10000 to 20000;
    }

## 数值划分
### 端口
	unsigned int max  = 6,55,35
	[项目id][服务id][程序id]
	eg:
	gate:
		1,01,01
        1,01,02
    group:
		1,02,01
		1,02,02

### 错误码
    unsigned int max  = 4,294,967,295
    eg:
    gate:
        (1,001,000,000 - 1,001,999,999]
    group:
        (1,002,000,000 - 1,002,999,999]

## 资源管理服务
### 模块列表
    module.conf
    {
        "module_list": [
            {
                "module": "gate",
                "depend_file": "depend_gate.conf",
                "idc_file": "idc_gate.conf",
                "kv_file": "kv_gate.conf"
            },
            {
                "module": "group",
                "depend_file": "depend_group.conf",
                "idc_file": "idc_group.conf",
                "kv_file": "kv_group.conf"
            }
        ]
    }

### 模块依列表
    depend_gate.conf
    {
        "module": "gate",
        "depend_list": [
            {
                "module": "group"
            },
            {
                "module": "buddy"
            }
        ]
    }

### 模块IDC列表
    idc_gate.conf
    {
        "module": "gate",
        "idc_list": [
            {
                "idc": "shenzhen_01",						//地区机房分组
                "set_list": [
                    {
                        "set": "set_01",					//机房内部分组
                        "heartbeat": {
                            "heartbeat_ip": "out_ip",		//用out_ip或inner_ip做心跳
							"heartbeat_gap": 5,				//心跳探测间隔
							"lose_time": 3,					//服务丢失次数
                            "recover_time": 3				//服务恢复次数
                        }
                        "heartbeat_list": [
                            {
                                "id": "id_01",
                                "inner_ip": "121.1.1.1",	//外网ip,没外网填内网ip
                                "out_ip":  "11.1.1.1",		//内网ip
                                "port": 10101
                            }
                        ],
                        "service_list": [
                            {
                                "id": "id_02",
                                "inner_ip": "121.1.1.2",
                                "out_ip":  "11.1.1.2",
                                "port": 10102
                            }
                        ]
                    }
                ]
            }
        ]
    }

### 模块kv配置列表
    kv_gate.conf
    {
        "module": "gate",
        "kv_list": [
            {
                "key": "timeout",
                "val": "30"
            },
            {
                "key": "env",
                "val": "test"
            }
        ]
    }


