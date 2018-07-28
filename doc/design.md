# balancer

# 目录
[toc]

## 数值划分

### 服务id
    unsigned short max  = 65535
    eg:
    gate:
        11000
    group:
        12000

### 端口
    unsigned short max  = 65535
    [服务id]+[程序id(绑定的cpu号)]
    eg:
    gate:
        tcp: 10100 = 10100 + 0, http: 10150 = 10100 + 50 + 0   //绑定cpu 0
        tcp: 10101 = 10100 + 1, http: 10151 = 10100 + 50 + 1   //绑定cpu 1
        tcp: 10102 = 10100 + 2, http: 10152 = 10100 + 50 + 2   //绑定cpu 2
    group:
        tcp: 10200 = 10200 + 0, http: 10250 = 10200 + 50 + 0
        tcp: 10201 = 10200 + 1, http: 10251 = 10200 + 50 + 1
        tcp: 10202 = 10200 + 2, http: 10252 = 10200 + 50 + 2

### 错误码
    unsigned int max  = 42949,67295
    [服务id] * 100000 + [错误码(00000-99999)]
    eg:
    gate:
        (10100,00000 - 10100,99999]
    group:
        (10200,00000 - 10200,99999]

## 消息设计

### 数据包格式
    HLV格式

    struct Packet
    {
        unsigned int            header              :4              // 包头标识
        unsigned int            len                 :4              // 长度
        unsigned short          version             :2              // 协议版本
        unsigned short          from_service_id     :2              // 发送的service_id
        unsigned short          to_service_id       :2              // 发送到service_id
        unsigned int            to_proc_id          :4              // 0为负载均衡，非0则请求到proc_id的服务
        unsigned int            app_id              :4
        unsigned int            app_version         :4
        unsigned long long      conn_seq_id         :8              // 客户端连接序列id(用在网关转发)
        unsigned long long      msg_seq_id          :8              // 消息序列id
        unsigned char           data_format         :1              // 数据格式，详见data_format.proto
        unsigned char           reserve_field_0     :1              // 保留字段0
        unsigned int            reserve_field_1     :4              // 保留字段1
        unsigned int            reserve_field_2     :4              // 保留字段2
        unsigned int            reserve_field_3     :4              // 保留字段3
        unsigned char           data[]              :data_len
        unsigned int            check_sum           :4              // 校验和
    }

    header = [0x00,0x00,0x00,0x00]

    len = sizeof(version + from_service_id + to_service_id + to_proc_id + app_id + app_version +
                 conn_seq_id + msg_seq_id + data_format + reserve_field[4] + check_sum) + data_len

    len(Packet) = 60 + data_len = [60, (unsigned short)-1]

    check_sum = adler32(len + version + from_service_id + to_service_id + to_proc_id + app_id + app_version +
                        conn_seq_id + msg_seq_id + data_format + reserve_field[4] + data[])

### data
    common.proto

    // 公共错误码
    enum ErrorCode {
        SUCCESS                         = 0;

        // 公共系统错误码 (各个服务service_id * 100000 + 公共系统错误码)
        ERR_SYS_BEGIN                   = 100;
        ERR_SYS_OVERLOAD                = 101;          // 服务过载
        ERR_SYS_REJECT_SERVICE          = 102;          // 拒绝服务
        ERR_SYS_SERVER_INNER            = 103;          // 服务内部错误
        ERR_SYS_TIMEOUT                 = 104;          // 超时错误
        ERR_SYS_NO_INSERVICE_LIST       = 105;          // 没有可用服务ip
        ERR_SYS_TASK_STATE              = 106;          // 任务状态错误
        ERR_SYS_TASK_DISCARD            = 107;          // 任务丢弃
        ERR_SYS_END                     = 199;

        // 公共数据包错误码 (各个服务service_id * 100000 + 公共数据包错误码)
        ERR_PACKET_BEGIN                = 200;
        ERR_PACKET_ENCODE               = 201;          // 打包失败
        ERR_PACKET_DECODE               = 202;          // 解码失败
        ERR_PACKET_HEADER               = 203;
        ERR_PACKET_LEN                  = 204;
        ERR_PACKET_VERSION              = 205;
        ERR_PACKET_FROM_SERVICE_ID      = 206;
        ERR_PACKET_TO_SERVICE_ID        = 207;
        ERR_PACKET_APP_ID               = 208;
        ERR_PACKET_APP_VERSION          = 209;
        ERR_PACKET_CONN_SEQ_ID          = 210;
        ERR_PACKET_MSG_SEQ_ID           = 211;
        ERR_PACKET_DATA_FORMAT          = 212;
        ERR_PACKET_DATA_FIELD_0         = 213;
        ERR_PACKET_DATA_FIELD_1         = 214;
        ERR_PACKET_DATA_FIELD_2         = 215;
        ERR_PACKET_DATA_FIELD_3         = 216;
        ERR_PACKET_CHECK_SUM            = 217;
        ERR_PACKET_UNKNOWN_REQUEST      = 218;          // 不明请求
        ERR_PACKET_END                  = 299;

        // 公共接口错误码 (各个服务service_id * 100000 + 公共接口错误码)
        ERR_INTERFACE_BEGIN             = 300;
        ERR_INTERFACE_PARAM             = 301;          // 参数错误
        ERR_INTERFACE_PERM              = 302;          // 权限错误
        ERR_INTERFACE_END               = 399;

        // 公共业务错误码 (各个服务service_id * 100000 + 公共业务错误码)
        ERR_BUSINESS_BEGIN              = 10000;
        ERR_BUSINESS_END                = 99999;
    }

#### protobuf 2
    data.proto

    message Body {
        optional uint32     error_code      = 1;        // rsp必填
        optional bytes      error_info      = 2;        // rsp必填

        extensions 10000 to 60000;                      // 扩展各个服务消息
    }

    gate.proto

    enum ErrorCode {
        ERR_BEGIN                       = 1010000000;

        // 系统错误码
        ERR_SYS_BEGIN                   = 1010000100;
        ERR_SYS_OVERLOAD                = 1010000101;       // 服务过载
        ERR_SYS_REJECT_SERVICE          = 1010000102;       // 拒绝服务
        ERR_SYS_SERVER_INNER            = 1010000103;       // 服务内部错误
        ERR_SYS_TIMEOUT                 = 1010000104;       // 超时错误
        ERR_SYS_NO_INSERVICE_LIST       = 1010000105;       // 没有可用服务ip
        ERR_SYS_TASK_STATE              = 1010000106;       // 任务状态错误
        ERR_SYS_TASK_DISCARD            = 1010000107;       // 任务丢弃
        ERR_SYS_END                     = 1010000199;

        // 数据包错误码
        ERR_PACKET_BEGIN                = 1010000200;
        ERR_PACKET_ENCODE               = 1010000201;          // 打包失败
        ERR_PACKET_DECODE               = 1010000202;          // 解码失败
        ERR_PACKET_HEADER               = 1010000203;
        ERR_PACKET_LEN                  = 1010000204;
        ERR_PACKET_VERSION              = 1010000205;
        ERR_PACKET_FROM_SERVICE_ID      = 1010000206;
        ERR_PACKET_TO_SERVICE_ID        = 1010000207;
        ERR_PACKET_APP_ID               = 1010000208;
        ERR_PACKET_APP_VERSION          = 1010000209;
        ERR_PACKET_CONN_SEQ_ID          = 1010000210;
        ERR_PACKET_MSG_SEQ_ID           = 1010000211;
        ERR_PACKET_DATA_FORMAT          = 1010000212;
        ERR_PACKET_DATA_FIELD_0         = 1010000213;
        ERR_PACKET_DATA_FIELD_1         = 1010000214;
        ERR_PACKET_DATA_FIELD_2         = 1010000215;
        ERR_PACKET_DATA_FIELD_3         = 1010000216;
        ERR_PACKET_CHECK_SUM            = 1010000217;
        ERR_PACKET_UNKNOWN_REQUEST      = 1010000218;          // 不明请求
        ERR_PACKET_END                  = 1010000299;

        // 接口错误码
        ERR_INTERFACE_BEGIN             = 1010000300;
        ERR_INTERFACE_PARAM             = 1010000301;       // 参数错误
        ERR_INTERFACE_PERM              = 1010000302;       // 权限错误
        ERR_INTERFACE_END               = 1010000399;

        // 业务错误码
        ERR_BUSINESS_BEGIN              = 1010010000;
        ERR_USERID_NO_EXIST             = 1010010001;

        ERR_END                         = 1010099999;
    }

    message GateMsg {                                       // 奇数是请求，偶数是响应
        oneof choice {
            LoginReq        login_req       = 1;            // 登录请求
            LoginRsp        login_rsp       = 2;            // 登录响应
        }
    }

    extend Data.Body {
        optional GateMsg    gate_msg        = 10100;        // gate的service_id
    }

#### protobuf 3
    data.proto

    message Body {
        oneof msg_type {
            MsgReq  msg_req = 1;
            MsgRsq  msg_rsp = 2;
        }

        google.protobuf.Any service_msg    = 3;        // 扩展各个服务消息


        message MsgReq {
            // 方便以后扩展
        }

        message MsgRsq {
            int32           code  = 1;
            bytes           info  = 2;
        }
    }

    gate.proto

    enum ErrorCode {
        SUCCESS                         = 0;

        ERR_BEGIN                       = 1010000000;

        // 系统错误码
        ERR_SYS_BEGIN                   = 1010000100;
        ERR_SYS_OVERLOAD                = 1010000101;       // 服务过载
        ERR_SYS_REJECT_SERVICE          = 1010000102;       // 拒绝服务
        ERR_SYS_SERVER_INNER            = 1010000103;       // 服务内部错误
        ERR_SYS_TIMEOUT                 = 1010000104;       // 超时错误
        ERR_SYS_NO_INSERVICE_LIST       = 1010000105;       // 没有可用服务ip
        ERR_SYS_TASK_STATE              = 1010000106;       // 任务状态错误
        ERR_SYS_TASK_DISCARD            = 1010000107;       // 任务丢弃
        ERR_SYS_END                     = 1010000199;

        // 数据包错误码
        ERR_PACKET_BEGIN                = 1010000200;
        ERR_PACKET_ENCODE               = 1010000201;          // 打包失败
        ERR_PACKET_DECODE               = 1010000202;          // 解码失败
        ERR_PACKET_HEADER               = 1010000203;
        ERR_PACKET_LEN                  = 1010000204;
        ERR_PACKET_VERSION              = 1010000205;
        ERR_PACKET_FROM_SERVICE_ID      = 1010000206;
        ERR_PACKET_TO_SERVICE_ID        = 1010000207;
        ERR_PACKET_APP_ID               = 1010000208;
        ERR_PACKET_APP_VERSION          = 1010000209;
        ERR_PACKET_CONN_SEQ_ID          = 1010000210;
        ERR_PACKET_MSG_SEQ_ID           = 1010000211;
        ERR_PACKET_DATA_FORMAT          = 1010000212;
        ERR_PACKET_DATA_FIELD_0         = 1010000213;
        ERR_PACKET_DATA_FIELD_1         = 1010000214;
        ERR_PACKET_DATA_FIELD_2         = 1010000215;
        ERR_PACKET_DATA_FIELD_3         = 1010000216;
        ERR_PACKET_CHECK_SUM            = 1010000217;
        ERR_PACKET_UNKNOWN_REQUEST      = 1010000218;          // 不明请求
        ERR_PACKET_END                  = 1010000299;

        // 接口错误码
        ERR_INTERFACE_BEGIN             = 1010000300;
        ERR_INTERFACE_PARAM             = 1010000301;       // 参数错误
        ERR_INTERFACE_PERM              = 1010000302;       // 权限错误
        ERR_INTERFACE_END               = 1010000399;

        // 业务错误码
        ERR_BUSINESS_BEGIN              = 1010010000;
        ERR_USERID_NO_EXIST             = 1010010001;

        ERR_END                         = 1010099999;
    }

    message GateMsg {                                       // 奇数是请求，偶数是响应
        oneof choice {
            LoginReq        login_req       = 1;            // 登录请求
            LoginRsp        login_rsp       = 2;            // 登录响应
        }
    }

## 服务类型
    send: ->
    recv: <-

    backend:
        center -> [navigate, gate, logic, proxy]
        (listen http * 1, connect tcp * n)
        10100:核心服务,cpu密集型,进程数等于cpu数

        navigate -> [], <- [client, gate]
        (listen http * 1, listen tcp * 1)
        10200:核心服务,cpu密集型,进程数等于cpu数

        gate -> [client, navigate, logic, proxy], <- [client, logic]
        (listen http * 1, listen tcp * 1, connect tcp * n)
        10300:核心服务,cpu密集型,进程数等于cpu数

        logic -> [proxy, gate], <- [gate]
        (listen http * 1, listen tcp * 1, connect tcp * n)
        10400:业务服务,cpu密集型,进程数等于cpu数

        proxy -> [], <-[gate, logic]
        (listen http * 1, listen tcp * 1)
        10500:业务服务,io密集型,进程数等于cpu数乘2或3

    frontend:
        client -> [navigate, gate], <- [gate]
        (listen http * 1, connect tcp * n)
        10600:业务服务,cpu密集型,进程数等于cpu数

### 资源管理服务

#### 服务列表
    service.conf
    {
        "service_list": [
            {
                "service": "gate",
                "service_id": 1,
                "heartbeat": {
                    "heartbeat_ip": in_ip",             // 用in_ip或out_ip做心跳
                    "heartbeat_gap": 5,                 // 心跳探测间隔
                    "lose_time": 3,                     // 服务丢失次数
                    "recover_time": 5                   // 服务恢复次数
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
                    "recover_time": 5
                },
                "file_path": {
                    "depend": "./depend_gate.conf",
                    "idc": "./idc_gate.conf",
                    "kv": "./kv_gate.conf"
                }
            }
        ]
    }

#### 服务依赖列表
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

#### 服务idc列表
    idc_gate.conf
    {
        "service": "gate",
        "idc_list": [
            {
                "idc": "shenzhen_01",                       // 地区机房分组
                "set_list": [
                    {
                        "set": "set_01",                    // 机房内部分组
                        "heartbeat_list": [
                            {
                                "id": "id_01",
                                "in_ip": "121.1.1.1",       // 内网ip
                                "out_ip": "11.1.1.1",       // 外网ip,没外网填内网ip
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

#### 模块kv配置列表
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

#### 集中简化
    proc_id编号规则 x[n]:y[2]:z[1]，相同service下不能重复
    x:机器编号
    y:该机器的进程编号(占两位)
    z:0为实体进程，非0为虚拟进程(占最后一位)

##### 字段检查:
    1.所有字段名必须存在
    2.字段值字符串不能为空
    3.字段值数值类型不能小于等于0
    4.service_map.service_id，service_map.service_name不能全局重复
    5.同一个service内，kv_map.key不能重复
    6.同一个service内，heartbeat_list.proc_id, inservice_list.proc_id不能重复
    7.同一个service内，depend_map.depend_service_name不能重复
    8.depend_map.depend_service_name必须存在service_map.service_name中

##### 读操作:
    1.查询，返回service_id，service_name列表
    2.根据service_id查询，返回service_id，service_name，heartbeat，depend_map，kv_map，heartbeat_list，inservice_list

##### 写操作:
    1.根据service_id，修改heartbeat成员值
    2.根据service_id，depend_service_id，增加depend_map的depend_service_id
    3.根据service_id，depend_service_id，删除depend_map的depend_service_id
    4.根据service_id，key，value，修改kv_map的key对应val
    5.根据service_id，key，value，增加kv_map的key，val
    6.根据service_id，key，删除kv_map的key，val
    7.根据service_id，proc_id，增加ip到heartbeat_list（上架）
    8.根据service_id，proc_id，从heartbeat_list中删除proc_id（下架）
    9.根据service_id，proc_id，从heartbeat_list的proc_id删除，增加到inservice_list（上线）
    10.根据service_id，proc_id，从inservice_list的proc_id删除，增加到heartbeat_list（下线）
    11.根据service_id，service_id，heartbeat增加service
    12.根据service_id，删除service

##### service.json
    {
        "service_map": [
            {
                "service_id": 10100,                //服务id
                "service_name": "gate",             //服务名
                "heartbeat": {
                    "heartbeat_enable": true,       //心跳开关 true和false
                    "heartbeat_gap": 5,             //心跳探测间隔
                    "lose_time": 3,                 //服务丢失次数
                    "recover_time": 5               //服务恢复次数
                },
                "depend_map": [                     //服务依赖
                    {
                        "depend_service_id": 10200  //依赖的service_id
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
                "heartbeat_list": [                 //上架(有心跳探测,不服务)
                    {
                        "proc_id": 1000,            //程序id
                        "proc_des": "gate_1_0_0",   //程序描述
                        "in_ip": "121.1.1.1",       //内网ip,心跳探测,服务通信(如果要跨机房通讯，全部用外网ip连接)
                        "out_ip": "11.1.1.1",       //外网ip,没外网ip就填内网ip
                        "port": 10100
                    }
                ],
                "inservice_list": [                 //上线(有心跳探测,在服务)
                    {
                        "proc_id": 2000,
                        "proc_des": "gate_2_0_0",
                        "in_ip": "121.1.1.2",
                        "out_ip": "11.1.1.2",
                        "port": 10100
                    },
                    {
                        "proc_id": 2001,
                        "proc_des": "gate_2_0_1_v",    //支持虚拟进程，gate_2_0_0和gate_2_0_1_v是同一个进程，变相给进程导流
                        "in_ip": "121.1.1.2",
                        "out_ip": "11.1.1.2",
                        "port": 10100
                    }
                ]
            },
            {
                "service_id": 10200,
                "service_name": "group",
                "heartbeat": {
                    "heartbeat_enable": true,
                    "heartbeat_gap": 5,
                    "lose_time": 3,
                    "recover_time": 5
                },
                "depend_map": [
                    {
                        "depend_service_id": 10100
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
                "heartbeat_list": [
                    {
                        "proc_id": 1000,
                        "proc_des": "group_1_0_0",
                        "in_ip": "121.1.1.10",
                        "out_ip": "11.1.1.10",
                        "port": 10200
                    }
                ],
                "inservice_list": [
                    {
                        "proc_id": 2000,
                        "proc_des": "group_2_0_0",
                        "in_ip": "121.1.1.20",
                        "out_ip": "11.1.1.20",
                        "port": 10200
                    },
                    {
                        "proc_id": 2010,
                        "proc_des": "group_2_1_0",
                        "in_ip": "121.1.1.21",
                        "out_ip": "11.1.1.21",
                        "port": 10201
                    }
                ]
            }
        ]
    }

#### 心跳探测
    message HeartbeatReq {
        int32      level               = 1;     // center的等级
        int32      service_id          = 2;
        uint32     proc_id             = 3;
        uint32     state               = 4;     // 目标进程状态:1.上架,2.上线
        uint64     conf_update_time    = 5;     // 配置更新时间(微妙)
        bytes      conf_json           = 6;     // 有配置更新下发json，无配置更新下发空字符串
    }

    message HeartbeatRsp {
        int32      level               = 1;     // 接管center的等级
        int32      service_id          = 2;     // 返回和HeartbeatReq.service_id的值一样
        uint32     proc_id             = 3;     // 返回和HeartbeatReq.proc_id的值一样
        uint64     conf_update_time    = 4;     // 配置更新时间(微妙)
        uint32     role_expire_time    = 5;     // 接管center的到期秒数，
                                                // 服务当前时间和接管center最新心跳请求时间相减秒数，
                                                // 非接管center根据role_expire_time判断是否需要接管服务
    }

#### 配置更新

#### 虚拟进程
    同一服务各个机器的配置不同，对于高配的机器的进程，通过给该进程虚拟多个proc_id，变相给该进程更多的请求
    注意，虚拟进程只能用在对状态（上架/上线）切换无特殊处理的服务（像gate就不合适，gate从上线到上架后要主动断开客户端连接）

#### 上架

#### 下架

#### 上线

#### 下线

#### 故障转移

#### 故障恢复

#### center之间配置同步
    service_type: center
    只有全局配置，先不搞局部配置和精细化控制
    同步配置(http请求定时查询同步)
    1 <-----2 <-----3 <--|
    |--------—-----------|

    1为最高角色，当1设置为‘同步’状态，2定时请求1拉的配置，当2请求配置跟新完毕后返回，1设置为‘同步中’，
    3定时请求2拉的配置，1定时请求拉3的配置，由于3等级比1小，3收到比自己大等级的请求说明自己是最后一个，
    返回3的配置信息，1收到3的返回比较本地配置信息，设置为‘同步完成’

### 导航服务
    service_type: navigate
    两种模式:
    A.请求导航服务服务返回gate的ip做一致性哈希，gate不发生变换的情况下，保证同一个user client重连还是重连到之前的gate服务
    B.返回在用户连接数最小的gate，gate和navigate人数同步，定时(30-60s)和定量(1-n个次数增加/减少变化)向所有navigate广播人数

    如果要统一外网端口或减少外网ip机器数量(成本)，则在前面放nginx转后到后方多个端口的navigate

### 网关服务
    service_type: gate
    （不考虑）gate要做user对tcp的绑定，保证user断开重连之后tcp连接不同，但还能找回user的新tcp连接
    每次gate被接管时，要赋值center发送给的proc_id，以便同步navigate时报上自己proc_id，方便navigate根据proc_id更新

### 逻辑服务
    service_type: logic

### 代理服务
    service_type: proxy
    数据库，第三方接口等对接

### 客户端
    service_type: client

## id生成
    用unsigned long long类型，占64位，单调递增

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
    对于client端，空闲连接大于60秒，关闭连接（隐藏条件是server端处理请求的时间要小于60秒）
    对于server端，空闲连接大于90秒，关闭连接

### 防串话

#### 更换id
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

    代价
    a.由于要替换id，如果有数据包中有check_sum且下游需要校验，则需要重新计算更新check_sum才能转发给下游服务；
      同时下游服务返回结果用新id找到老id，替换回老id重新计算check_sum转发给客户端;
      所以更换id不适合类型做网关类型服务（转发/透传），由于要更换id必须重新计算check_sum，浪费cpu资源。

    b.由于产生新的id替换，就有新id和老id的对应的映射关系，如果下游服务不返回结果，新id会一直存在导致资源泄露
      所以新id和老id的对应的映射关系要缓存起来且放入定时器中，同时加重定时器的负担；
      一定时间内下游服务的新id返回结果超时，要清理新id和老id的对应的映射关系，
      所以更换id不适合类型做网关类型服务（转发/透传），每个请求都要产生一个新老id映射放入定时器，
      同时网关也要维持大量客户端连接的定时器，定时器负担过重。

    所以更换id适用于logic类型服务

#### 服务端产生conn_id且不更换id

    由于每个客户端请求都有conn_id，网关程序则不需要更换id，无需加重定时器负担，无需重新计算crc，就可以转发给下游服务；
    下游服务返回结果带上客户端的conn_id，网关收到结果消息后无需重新计算crc和更换id，消息原封不同的直接根据conn_id返回给客户端，
    客户端收到返回结果要校验conn_id。
    服务端产生一个conn_id对应客户端一个连接，且conn_id是不会改变的
    数据包进进出出gate无需其他操作，定时器只需要维持客户端的连接。

    代价:
    客户端和网关建立连接后，第一个请求必须获取自己的conn_id，后面的请求带上conn_id，
    否则后面的客户端请求会因为conn_id校验失败被网关断开连接。
    所以客户端建立连接后，第一个请求发送conn_id为0，len为最小数据包长的请求（data_len为0）给网关，
    网关返回客户端的conn_id（网关必须要为每个客户端连接标记是否请求过conn_id，获取conn_id机会只有一次且只有第一次）

    所以服务端产生conn_id且不更换id适用于gate类型服务

    错误的方式： conn_id = [client_ip，client_port]
    网关服务使用客户端client_ip和client_port作为conn_id,虽然理论上五元组可作为key，
    [protocol，client_ip， client_port，server_ip，server_port]
    protocol为tcp不变，client_ip变化，client_port变化，server_ip不变，server_port不变
    则client_ip和client_port组合为key，为2^48个值。

    a.实际在单机上，client_ip是不变的，client_port是临时端口是变化的，操作系统会重复使用临时端口；
      可能出现某进程client_port刚回收，新进程connect产生client_port刚好等于之前回收client_port，虽然client_port值虽然没变，
      但已经是另外一个进程使用client_port，导致内部服务转发给网关还是之前的client_ip和client_port作为conn_id，
      网关拿这个conn_id转发客户端，这时conn_id已经是对应另外一个客户端进程，导致网关串话，虽然他们在同一台机器上的不同的进程。

    b.由于很多客户端是在内网发起connect对网关的连接，虽然他们在内网的不同机器上（每个内网机器对应不同的内网ip）；
      但从listen的网关来说，虽然客户端内网ip不同，但客户端的出口ip（外网ip）是一样的，等同于这些客户端共用同一个client_ip，
      由于每个内网机上的client_port是和网关看客户端的client_port是一致的，client_port有2^16个值，
      却表示整个内网所以机器上的client_port，大大增加client_port重复的概率。
      导致出现内网机器A内网ip_A的client_port刚回收，另外一个内网机器B内网ip_B的新进程connect产生client_port
      刚好等于之前回收内网机器A内网ip_A的client_port的值，由于所有内网机器出口ip是一样的，网关看client_port没变化，
      但客户端实际已经变了，导致网关串话，虽然他们在同一个内网里的不同的机器上。

    所以client_ip和client_port作为conn_id是不可靠的，不能有侥幸心理。


## 负载均衡

## 请求路由
    proc_id

## 过载保护

## 服务更新

### 无状态服务灰度发布

### 有状态服务灰度发布

## 就近接入
