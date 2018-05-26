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

## 服务角色
    backend:
        center -> [navigate, gate, middle, proxy]
        navigate <- client
        gate <- client, -> [navigate, middle, proxy]
        middle -> [proxy, gate]
        proxy -> [db, third party]

    frontend:
        client -> navigate, gate

## 资源管理服务
    service_role: center
    只有全局配置，先不搞局部配置和精细化控制

### 服务列表
    service.conf
    {
        "service_list": [
            {
                "service": "gate",
                "service_id": 1,
                "heartbeat": {
                    "heartbeat_ip": in_ip",             //用in_ip或out_ip做心跳
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
                        "inservice_list": [
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

#### 字段检查:
    1.所有字段名必须存在
    2.字段值字符串不能为空
    3.字段值数值类型不能小于等于0
    4.service_map.service，service_map.service_id不能全局重复
    5.同一个service内，kv_map.key不能重复
    6.同一个service内，heartbeat_map.proc_id, inservice_map.proc_id不能重复
    7.同一个service内,depend_map.depend_service不能重复
    8.depend_map.depend_service必须存在service_map.service中

#### 读操作:
    1.查询，返回service，service_id列表
    2.根据service查询，返回heartbeat，depend_map，kv_map，heartbeat_map，inservice_map

#### 写操作:
    1.根据service，修改heartbeat成员值
    2.根据service，depend_service，增加depend_map的depend_service
    3.根据service，depend_service，删除depend_map的depend_service
    4.根据service，key，value，修改kv_map的key对应val
    5.根据service，key，value，增加kv_map的key，val
    6.根据service，key，删除kv_map的key，val
    7.根据service，proc_id，增加ip到heartbeat_map（上架）
    8.根据service，proc_id，从heartbeat_map中删除ip（下架）
    9.根据service，proc_id，从heartbeat_map的ip删除，增加到inservice_map（上线）
    10.根据service，proc_id，从inservice_map的ip删除，增加到heartbeat_map（下线）
    11.根据service，service_id，heartbeat增加service
    12.根据service，删除service

#### service.conf
    {
        "service_map": [
            {
                "service": "gate",                  //服务名
                "service_id": 11000,                //服务id
                "heartbeat": {
                    "heartbeat_enable": true,       //心跳开关 true和false
                    "heartbeat_gap": 5,             //心跳探测间隔
                    "lose_time": 3,                 //服务丢失次数
                    "recover_time": 3               //服务恢复次数
                },
                "depend_map": [                     //服务依赖
                    {
                        "depend_service": "group"
                    }
                ],
                "kv_map": [                         //kv配置参数
                    {
                        "key": "timeout",
                        "val": "30"
                    },
                    {
                        "key": "env",
                        "val": "test"
                    }
                ],
                "heartbeat_map": [                  //上架(有心跳探测,不服务)
                    {
                        "proc_id": "gate_001",
                        "in_ip": "121.1.1.1",       //内网ip,心跳探测,服务通信
                        "out_ip": "11.1.1.1",       //外网ip,没外网ip就填内网ip
                        "port": 11001
                    }
                ],
                "inservice_map": [                  //上线(有心跳探测,在服务)
                    {
                        "proc_id": "gate_002",
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
                    "heartbeat_gap": 5,
                    "lose_time": 3,
                    "recover_time": 3
                },
                "depend_map": [
                    {
                        "depend_service": "gate"
                    }
                ],
                "kv_map": [
                    {
                        "key": "name_max_size",
                        "val": "1024"
                    },
                    {
                        "key": "buffer_max_size",
                        "val": "1024"
                    }
                ],
                "heartbeat_map": [
                    {
                        "proc_id": "group_001",
                        "in_ip": "121.1.1.10",
                        "out_ip": "11.1.1.10",
                        "port": 11001
                    }
                ],
                "inservice_map": [
                    {
                        "proc_id": "group_002",
                        "in_ip": "121.1.1.20",
                        "out_ip": "11.1.1.20",
                        "port": 11002
                    }
                ]
            }
        ]
    }


## 导航服务
    service_role: navigate
    请求导航服务服务返回gate的ip做一致性哈希，gate不发生变换的情况下，
    保证同一个user client重连还是重连到之前的gate服务

## 网关服务
    service_role: gate
    （暂不考虑）gate要做user对tcp的绑定，保证user断开重连之后tcp连接不同，但还能找回user的新tcp连接

## 业务服务
    service_role: middle

## 代理服务
    service_role: proxy
    数据库，第三方接口等对接

## 客户端
    service_role: client

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