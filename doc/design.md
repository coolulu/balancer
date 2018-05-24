# balancer

# 目录
[toc]

## 消息设计

### 数据包格式
    HLV格式
    struct Packet
    {
        unsigned int        head            :4
        unsigned int        len             :4
        unsigned short      version         :2
        unsigned short      service_id      :2
        unsigned int        app_id          :4
        unsigned int        session_id      :4
        unsigned char       data[]          :data_len
        unsigned int        crc             :4
    }
    head = [0x00,0x00,0x00,0x00]
    len = len(version + service_id + app_id + session_id + data_len + crc)
    len(Packet) = 24 + data_len = [24, (unsigned short)-1]
    crc = crc(len + version + service_id + app_id + session_id + data[])

### message.proto
    message Message
    {
        repeated uint64     timestamp       = 1;    //请求源或返回源的时间(比如App客户端发送时间)
        optional uint32     error_code      = 2;    //rsp必填
        optional bytes      error_info      = 3;    //rsp必填
        extensions 10000 to 20000;
    }

## 数值划分

### 服务id
    unsigned int max  = 4,294,967,295
    eg:
    gate:
        11,000
        11,000
    group:
        12,000
        12,000

### 端口
    unsigned short max  = 65,535
    [服务id]+[程序id]
    eg:
    gate:
        11,001 = 11,000 + 1
        11,002 = 11,000 + 2
    group:
        12,001 = 12,000 + 1
        12,002 = 12,000 + 2

### 错误码
    unsigned int max  = 4,294,967,295
    [服务id]*100,000+[错误码(00,000-99,999)]
    eg:
    gate:
        (11,000,00,000 - 11,000,99,999]
    group:
        (12,000,00,000 - 12,000,99,999]

## 资源管理服务
    只有全局配置，先不搞局部配置

### 服务列表
    server.conf
    {
        "server_list": [
            {
                "service": "gate",
                "service_id": 1,
                "heartbeat": {
                    "heartbeat_ip": in_ip",           //用in_ip或out_ip做心跳
                    "heartbeat_gap": 5,                 //心跳探测间隔
                    "lose_time": 3,                     //服务丢失次数
                    "recover_time": 3                   //服务恢复次数
                },
                "file_path": {
                    "depend": "./depend_gate.conf",
                    "idc": "./idc_gate.conf",
                    "kv": "./kv_gate.conf"
                }
            },
            {
                "service": "group",
                "service_id": 2,
                "heartbeat": {
                    "heartbeat_ip": "out_ip",
                    "heartbeat_gap": 5,
                    "lose_time": 3,
                    "recover_time": 3
                },
                "file_path": {
                    "depend": "./depend_gate.conf",
                    "idc": "./idc_gate.conf",
                    "kv": "./kv_gate.conf"
                }
            }
        ]
    }

### 服务依赖列表
    不搞依赖表，全局广播依赖，各服务自行决定取自己的依赖
    depend_gate.conf
    {
        "service": "gate",
        "depend_list": [
            {
                "service": "group"
            },
            {
                "service": "buddy"
            }
        ]
    }

### 服务idc列表
    idc_gate.conf
    {
        "service": "gate",
        "idc_list": [
            {
                "idc": "shenzhen_01",                       //地区机房分组
                "set_list": [
                    {
                        "set": "set_01",                    //机房内部分组
                        "heartbeat_list": [
                            {
                                "id": "id_01",
                                "in_ip": "121.1.1.1",       //内网ip
                                "out_ip": "11.1.1.1",       //外网ip,没外网填内网ip
                                "port": 11001
                            }
                        ],
                        "service_list": [
                            {
                                "id": "id_02",
                                "in_ip": "121.1.1.2",
                                "out_ip": "11.1.1.2",
                                "port": 11002
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
        "service": "gate",
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

### 集中简化
    service.conf
    {
        "service_list": [
            {
                "service": "gate",
                "service_id": 11000,
                "heartbeat": {
                    "heartbeat_ip": "in_ip",        //用in_ip或out_ip做心跳
                    "heartbeat_gap": 5,             //心跳探测间隔
                    "lose_time": 3,                 //服务丢失次数
                    "recover_time": 3               //服务恢复次数
                },
                "kv_list": [
                    {
                        "key": "timeout",
                        "val": "30"
                    },
                    {
                        "key": "env",
                        "val": "test"
                    }
                ],
                "heartbeat_list": [
                    {
                        "id": "gate_001",
                        "in_ip": "121.1.1.1",       //内网ip
                        "out_ip": "11.1.1.1",       //外网ip,没外网填内网ip
                        "port": 11001
                    }
                ],
                "service_list": [
                    {
                        "id": "gate_002",
                        "in_ip": "121.1.1.2",
                        "out_ip": "11.1.1.2",
                        "port": 11002
                    }
                ]
            },
            {
                "service": "group",
                "service_id": 12000,
                "heartbeat": {
                    "heartbeat_ip": "out_ip",
                    "heartbeat_gap": 5,
                    "lose_time": 3,
                    "recover_time": 3
                },
                "kv_list": [
                    {
                        "key": "name_max_size",
                        "val": "1024"
                    },
                    {
                        "key": "buffer_max_size",
                        "val": "1024"
                    }
                ],
                "heartbeat_list": [
                    {
                        "id": "group_001",
                        "in_ip": "121.1.1.10",
                        "out_ip": "11.1.1.10",
                        "port": 11001
                    }
                ],
                "service_list": [
                    {
                        "id": "group_002",
                        "in_ip": "121.1.1.20",
                        "out_ip": "11.1.1.20",
                        "port": 11002
                    }
                ]
            }
        ]
    }


## 导航服务
    请求导航服务服务返回gate的ip做一致性哈希，gate不发生变换的情况下，
    保证同一个user client重连还是重连到之前的gate服务

## 网关服务
    （暂不考虑）gate要做user对tcp的绑定，保证user断开重连之后tcp连接不同，但还能找回user的新tcp连接

## 业务服务

## 数据库代理服务

## 客户端

## id生成
    用unsigned long long类型，占64位

    高32位放时间戳（time（NULL）），unsigned int类型
    time_t强制转换成unsigned int，有数值损失，但只要在unsigned int最大值之内，
    unsigned int max = 4294967295，即2106/2/7 14:28:15，
    及2106年之前都是准确的，即使超时2106也是可以使用的

    低32位放count，count从0开始，每次使用加1，unsigned int类型
    unsigned int从0到最大值在翻转回0一圈，在现有的机器上循环要6-9秒，
    所以只要保证机器遍历一圈的耗时超过1秒，那么id = time（NULL） + count就不会重复

## 连接管理

### 连接断开条件
    对于内网服务之间的连接，简化断开方式和请求的返回不丢失，
    优先client先关闭闲置连接，若长久不断开闲置连接，可认为客户端出问题，则服务端才断开连接
    对于client端，空闲连接大于60秒，关闭连接（隐藏条件是客户端处理请求的时间要小于60秒）
    对于server端，空闲连接大于90秒，关闭连接

### 防串话
    不同连接下的相同请求id的处理，需要程序内部替换本程序唯一id，
    防止不同客户端连接但相同的id请求的返回串话

    client连接id和client连接的map
    id_tcp_client_1（id_1） -> tcp_client_1
    id_tcp_client_2（id_2） -> tcp_client_2
    id_tcp_client_3（id_3） -> tcp_client_3

    server的父任务id和（客户端连接的请求id，client连接id）的map
    id_server_1(id_4) -> {id_client_1_req_1, id_tcp_client_1}
    id_server_2(id_5) -> {id_client_1_req_2, id_tcp_client_1}
    id_server_3(id_6) -> {id_client_1_req_3, id_tcp_client_1}
    id_server_5(id_7) -> {id_client_2_req_1, id_tcp_client_2}
    id_server_6(id_8) -> {id_client_2_req_2, id_tcp_client_2}
    id_server_7(id_9) -> {id_client_3_req_1, id_tcp_client_3}

    id_client_X_req_Y：由client端产生，同一client端的id不能重复，不同client端的id可以重复
    id_X：由server端产生，保证连接id（id_tcp_client_1），父任务id（id_server_X），子任务id不重复

    流程
    tcp_client_1和server建立连接生成id_tcp_client_1（id_1）
    收到id_client_1_req_1请求，server产生父任务id_server_1(id_4)替换id_client_1_req_1请求
    若需要转发产生子任务id
    最后处理完毕后，根据id_server_1找回id_client_1_req_1替换返回id，
    根据id_tcp_client_1找到tcp_client_1，发送给tcp_client_1