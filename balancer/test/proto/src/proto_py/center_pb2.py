# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: center.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import common_pb2 as common__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='center.proto',
  package='center',
  syntax='proto3',
  serialized_pb=_b('\n\x0c\x63\x65nter.proto\x12\x06\x63\x65nter\x1a\x0c\x63ommon.proto\"\xa5\x02\n\tCenterMsg\x12#\n\x08test_req\x18\x01 \x01(\x0b\x32\x0f.common.TestReqH\x00\x12#\n\x08test_rsp\x18\x02 \x01(\x0b\x32\x0f.common.TestRspH\x00\x12-\n\rheartbeat_req\x18\x03 \x01(\x0b\x32\x14.center.HeartbeatReqH\x00\x12-\n\rheartbeat_rsp\x18\x04 \x01(\x0b\x32\x14.center.HeartbeatRspH\x00\x12\x32\n\x10sync_service_req\x18\x05 \x01(\x0b\x32\x16.center.SyncServiceReqH\x00\x12\x32\n\x10sync_service_rsp\x18\x06 \x01(\x0b\x32\x16.center.SyncServiceRspH\x00\x42\x08\n\x06\x63hoice\"~\n\x0cHeartbeatReq\x12\r\n\x05level\x18\x01 \x01(\x05\x12\x12\n\nservice_id\x18\x02 \x01(\x05\x12\x0f\n\x07proc_id\x18\x03 \x01(\r\x12\r\n\x05state\x18\x04 \x01(\r\x12\x18\n\x10\x63onf_update_time\x18\x05 \x01(\x04\x12\x11\n\tconf_json\x18\x06 \x01(\x0c\"s\n\x0cHeartbeatRsp\x12\r\n\x05level\x18\x01 \x01(\x05\x12\x12\n\nservice_id\x18\x02 \x01(\x05\x12\x0f\n\x07proc_id\x18\x03 \x01(\r\x12\x18\n\x10\x63onf_update_time\x18\x04 \x01(\x04\x12\x15\n\rexpire_second\x18\x05 \x01(\r\"*\n\x0eSyncServiceReq\x12\x18\n\x10\x63onf_update_time\x18\x01 \x01(\x04\"=\n\x0eSyncServiceRsp\x12\x18\n\x10\x63onf_update_time\x18\x01 \x01(\x04\x12\x11\n\tconf_json\x18\x02 \x01(\x0c*\xf4\t\n\tErrorCode\x12\x0b\n\x07SUCCESS\x10\x00\x12\x10\n\tERR_BEGIN\x10\xc0\xc6\x94\x30\x12\x14\n\rERR_SYS_BEGIN\x10\xa4\xc7\x94\x30\x12\x17\n\x10\x45RR_SYS_OVERLOAD\x10\xa5\xc7\x94\x30\x12\x1d\n\x16\x45RR_SYS_REJECT_SERVICE\x10\xa6\xc7\x94\x30\x12\x1b\n\x14\x45RR_SYS_SERVER_INNER\x10\xa7\xc7\x94\x30\x12\x16\n\x0f\x45RR_SYS_TIMEOUT\x10\xa8\xc7\x94\x30\x12 \n\x19\x45RR_SYS_NO_INSERVICE_LIST\x10\xa9\xc7\x94\x30\x12\x19\n\x12\x45RR_SYS_TASK_STATE\x10\xaa\xc7\x94\x30\x12\x1b\n\x14\x45RR_SYS_TASK_DISCARD\x10\xab\xc7\x94\x30\x12\x12\n\x0b\x45RR_SYS_END\x10\x87\xc8\x94\x30\x12\x17\n\x10\x45RR_PACKET_BEGIN\x10\x88\xc8\x94\x30\x12\x18\n\x11\x45RR_PACKET_ENCODE\x10\x89\xc8\x94\x30\x12\x18\n\x11\x45RR_PACKET_DECODE\x10\x8a\xc8\x94\x30\x12\x18\n\x11\x45RR_PACKET_HEADER\x10\x8b\xc8\x94\x30\x12\x15\n\x0e\x45RR_PACKET_LEN\x10\x8c\xc8\x94\x30\x12\x19\n\x12\x45RR_PACKET_VERSION\x10\x8d\xc8\x94\x30\x12!\n\x1a\x45RR_PACKET_FROM_SERVICE_ID\x10\x8e\xc8\x94\x30\x12\x1f\n\x18\x45RR_PACKET_TO_SERVICE_ID\x10\x8f\xc8\x94\x30\x12\x18\n\x11\x45RR_PACKET_APP_ID\x10\x90\xc8\x94\x30\x12\x1d\n\x16\x45RR_PACKET_APP_VERSION\x10\x91\xc8\x94\x30\x12\x1d\n\x16\x45RR_PACKET_CONN_SEQ_ID\x10\x92\xc8\x94\x30\x12\x1c\n\x15\x45RR_PACKET_MSG_SEQ_ID\x10\x93\xc8\x94\x30\x12\x1d\n\x16\x45RR_PACKET_DATA_FORMAT\x10\x94\xc8\x94\x30\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_0\x10\x95\xc8\x94\x30\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_1\x10\x96\xc8\x94\x30\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_2\x10\x97\xc8\x94\x30\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_3\x10\x98\xc8\x94\x30\x12\x1b\n\x14\x45RR_PACKET_CHECK_SUM\x10\x99\xc8\x94\x30\x12!\n\x1a\x45RR_PACKET_UNKNOWN_REQUEST\x10\x9a\xc8\x94\x30\x12\x15\n\x0e\x45RR_PACKET_END\x10\xeb\xc8\x94\x30\x12\x1a\n\x13\x45RR_INTERFACE_BEGIN\x10\xec\xc8\x94\x30\x12\x1a\n\x13\x45RR_INTERFACE_PARAM\x10\xed\xc8\x94\x30\x12\x19\n\x12\x45RR_INTERFACE_PERM\x10\xee\xc8\x94\x30\x12\x1c\n\x15\x45RR_INTERFACE_TIMEOUT\x10\xef\xc8\x94\x30\x12#\n\x1c\x45RR_INTERFACE_MASTER_TIMEOUT\x10\xf0\xc8\x94\x30\x12 \n\x19\x45RR_INTERFACE_SUB_TIMEOUT\x10\xf1\xc8\x94\x30\x12\x18\n\x11\x45RR_INTERFACE_END\x10\xcf\xc9\x94\x30\x12\x19\n\x12\x45RR_BUSINESS_BEGIN\x10\xa8\xce\x94\x30\x12!\n\x1a\x45RR_PROBER_SERVICE_TIMEOUT\x10\xa9\xce\x94\x30\x12\x1c\n\x15\x45RR_PROBER_SERVICE_ID\x10\xaa\xce\x94\x30\x12\"\n\x1b\x45RR_PROBER_CONF_JSON_TO_MAP\x10\xab\xce\x94\x30\x12#\n\x1c\x45RR_PROBER_CONF_LOAD_IP_INFO\x10\xac\xce\x94\x30\x12\x17\n\x10\x45RR_BUSINESS_END\x10\xcf\x94\x95\x30*7\n\x05State\x12\x0f\n\x0bSTATE_BEGIN\x10\x00\x12\r\n\tHEARTBEAT\x10\x64\x12\x0e\n\tINSERVICE\x10\xc8\x01*)\n\x05Level\x12\x0f\n\x0bLEVEL_BEGIN\x10\x00\x12\x0f\n\nINIT_LEVEL\x10\xe8\x07\x62\x06proto3')
  ,
  dependencies=[common__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

_ERRORCODE = _descriptor.EnumDescriptor(
  name='ErrorCode',
  full_name='center.ErrorCode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SUCCESS', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BEGIN', index=1, number=101000000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_BEGIN', index=2, number=101000100,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_OVERLOAD', index=3, number=101000101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_REJECT_SERVICE', index=4, number=101000102,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_SERVER_INNER', index=5, number=101000103,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TIMEOUT', index=6, number=101000104,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_NO_INSERVICE_LIST', index=7, number=101000105,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TASK_STATE', index=8, number=101000106,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TASK_DISCARD', index=9, number=101000107,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_END', index=10, number=101000199,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_BEGIN', index=11, number=101000200,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_ENCODE', index=12, number=101000201,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DECODE', index=13, number=101000202,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_HEADER', index=14, number=101000203,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_LEN', index=15, number=101000204,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_VERSION', index=16, number=101000205,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_FROM_SERVICE_ID', index=17, number=101000206,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_TO_SERVICE_ID', index=18, number=101000207,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_APP_ID', index=19, number=101000208,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_APP_VERSION', index=20, number=101000209,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_CONN_SEQ_ID', index=21, number=101000210,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_MSG_SEQ_ID', index=22, number=101000211,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FORMAT', index=23, number=101000212,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_0', index=24, number=101000213,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_1', index=25, number=101000214,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_2', index=26, number=101000215,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_3', index=27, number=101000216,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_CHECK_SUM', index=28, number=101000217,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_UNKNOWN_REQUEST', index=29, number=101000218,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_END', index=30, number=101000299,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_BEGIN', index=31, number=101000300,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_PARAM', index=32, number=101000301,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_PERM', index=33, number=101000302,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_TIMEOUT', index=34, number=101000303,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_MASTER_TIMEOUT', index=35, number=101000304,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_SUB_TIMEOUT', index=36, number=101000305,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_END', index=37, number=101000399,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_BEGIN', index=38, number=101001000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PROBER_SERVICE_TIMEOUT', index=39, number=101001001,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PROBER_SERVICE_ID', index=40, number=101001002,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PROBER_CONF_JSON_TO_MAP', index=41, number=101001003,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PROBER_CONF_LOAD_IP_INFO', index=42, number=101001004,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_END', index=43, number=101009999,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=687,
  serialized_end=1955,
)
_sym_db.RegisterEnumDescriptor(_ERRORCODE)

ErrorCode = enum_type_wrapper.EnumTypeWrapper(_ERRORCODE)
_STATE = _descriptor.EnumDescriptor(
  name='State',
  full_name='center.State',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='STATE_BEGIN', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='HEARTBEAT', index=1, number=100,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='INSERVICE', index=2, number=200,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=1957,
  serialized_end=2012,
)
_sym_db.RegisterEnumDescriptor(_STATE)

State = enum_type_wrapper.EnumTypeWrapper(_STATE)
_LEVEL = _descriptor.EnumDescriptor(
  name='Level',
  full_name='center.Level',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='LEVEL_BEGIN', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='INIT_LEVEL', index=1, number=1000,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=2014,
  serialized_end=2055,
)
_sym_db.RegisterEnumDescriptor(_LEVEL)

Level = enum_type_wrapper.EnumTypeWrapper(_LEVEL)
SUCCESS = 0
ERR_BEGIN = 101000000
ERR_SYS_BEGIN = 101000100
ERR_SYS_OVERLOAD = 101000101
ERR_SYS_REJECT_SERVICE = 101000102
ERR_SYS_SERVER_INNER = 101000103
ERR_SYS_TIMEOUT = 101000104
ERR_SYS_NO_INSERVICE_LIST = 101000105
ERR_SYS_TASK_STATE = 101000106
ERR_SYS_TASK_DISCARD = 101000107
ERR_SYS_END = 101000199
ERR_PACKET_BEGIN = 101000200
ERR_PACKET_ENCODE = 101000201
ERR_PACKET_DECODE = 101000202
ERR_PACKET_HEADER = 101000203
ERR_PACKET_LEN = 101000204
ERR_PACKET_VERSION = 101000205
ERR_PACKET_FROM_SERVICE_ID = 101000206
ERR_PACKET_TO_SERVICE_ID = 101000207
ERR_PACKET_APP_ID = 101000208
ERR_PACKET_APP_VERSION = 101000209
ERR_PACKET_CONN_SEQ_ID = 101000210
ERR_PACKET_MSG_SEQ_ID = 101000211
ERR_PACKET_DATA_FORMAT = 101000212
ERR_PACKET_DATA_FIELD_0 = 101000213
ERR_PACKET_DATA_FIELD_1 = 101000214
ERR_PACKET_DATA_FIELD_2 = 101000215
ERR_PACKET_DATA_FIELD_3 = 101000216
ERR_PACKET_CHECK_SUM = 101000217
ERR_PACKET_UNKNOWN_REQUEST = 101000218
ERR_PACKET_END = 101000299
ERR_INTERFACE_BEGIN = 101000300
ERR_INTERFACE_PARAM = 101000301
ERR_INTERFACE_PERM = 101000302
ERR_INTERFACE_TIMEOUT = 101000303
ERR_INTERFACE_MASTER_TIMEOUT = 101000304
ERR_INTERFACE_SUB_TIMEOUT = 101000305
ERR_INTERFACE_END = 101000399
ERR_BUSINESS_BEGIN = 101001000
ERR_PROBER_SERVICE_TIMEOUT = 101001001
ERR_PROBER_SERVICE_ID = 101001002
ERR_PROBER_CONF_JSON_TO_MAP = 101001003
ERR_PROBER_CONF_LOAD_IP_INFO = 101001004
ERR_BUSINESS_END = 101009999
STATE_BEGIN = 0
HEARTBEAT = 100
INSERVICE = 200
LEVEL_BEGIN = 0
INIT_LEVEL = 1000



_CENTERMSG = _descriptor.Descriptor(
  name='CenterMsg',
  full_name='center.CenterMsg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='test_req', full_name='center.CenterMsg.test_req', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='test_rsp', full_name='center.CenterMsg.test_rsp', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='heartbeat_req', full_name='center.CenterMsg.heartbeat_req', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='heartbeat_rsp', full_name='center.CenterMsg.heartbeat_rsp', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sync_service_req', full_name='center.CenterMsg.sync_service_req', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sync_service_rsp', full_name='center.CenterMsg.sync_service_rsp', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='choice', full_name='center.CenterMsg.choice',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=39,
  serialized_end=332,
)


_HEARTBEATREQ = _descriptor.Descriptor(
  name='HeartbeatReq',
  full_name='center.HeartbeatReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='level', full_name='center.HeartbeatReq.level', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='service_id', full_name='center.HeartbeatReq.service_id', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='proc_id', full_name='center.HeartbeatReq.proc_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='state', full_name='center.HeartbeatReq.state', index=3,
      number=4, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='conf_update_time', full_name='center.HeartbeatReq.conf_update_time', index=4,
      number=5, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='conf_json', full_name='center.HeartbeatReq.conf_json', index=5,
      number=6, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=334,
  serialized_end=460,
)


_HEARTBEATRSP = _descriptor.Descriptor(
  name='HeartbeatRsp',
  full_name='center.HeartbeatRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='level', full_name='center.HeartbeatRsp.level', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='service_id', full_name='center.HeartbeatRsp.service_id', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='proc_id', full_name='center.HeartbeatRsp.proc_id', index=2,
      number=3, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='conf_update_time', full_name='center.HeartbeatRsp.conf_update_time', index=3,
      number=4, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='expire_second', full_name='center.HeartbeatRsp.expire_second', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=462,
  serialized_end=577,
)


_SYNCSERVICEREQ = _descriptor.Descriptor(
  name='SyncServiceReq',
  full_name='center.SyncServiceReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='conf_update_time', full_name='center.SyncServiceReq.conf_update_time', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=579,
  serialized_end=621,
)


_SYNCSERVICERSP = _descriptor.Descriptor(
  name='SyncServiceRsp',
  full_name='center.SyncServiceRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='conf_update_time', full_name='center.SyncServiceRsp.conf_update_time', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='conf_json', full_name='center.SyncServiceRsp.conf_json', index=1,
      number=2, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=623,
  serialized_end=684,
)

_CENTERMSG.fields_by_name['test_req'].message_type = common__pb2._TESTREQ
_CENTERMSG.fields_by_name['test_rsp'].message_type = common__pb2._TESTRSP
_CENTERMSG.fields_by_name['heartbeat_req'].message_type = _HEARTBEATREQ
_CENTERMSG.fields_by_name['heartbeat_rsp'].message_type = _HEARTBEATRSP
_CENTERMSG.fields_by_name['sync_service_req'].message_type = _SYNCSERVICEREQ
_CENTERMSG.fields_by_name['sync_service_rsp'].message_type = _SYNCSERVICERSP
_CENTERMSG.oneofs_by_name['choice'].fields.append(
  _CENTERMSG.fields_by_name['test_req'])
_CENTERMSG.fields_by_name['test_req'].containing_oneof = _CENTERMSG.oneofs_by_name['choice']
_CENTERMSG.oneofs_by_name['choice'].fields.append(
  _CENTERMSG.fields_by_name['test_rsp'])
_CENTERMSG.fields_by_name['test_rsp'].containing_oneof = _CENTERMSG.oneofs_by_name['choice']
_CENTERMSG.oneofs_by_name['choice'].fields.append(
  _CENTERMSG.fields_by_name['heartbeat_req'])
_CENTERMSG.fields_by_name['heartbeat_req'].containing_oneof = _CENTERMSG.oneofs_by_name['choice']
_CENTERMSG.oneofs_by_name['choice'].fields.append(
  _CENTERMSG.fields_by_name['heartbeat_rsp'])
_CENTERMSG.fields_by_name['heartbeat_rsp'].containing_oneof = _CENTERMSG.oneofs_by_name['choice']
_CENTERMSG.oneofs_by_name['choice'].fields.append(
  _CENTERMSG.fields_by_name['sync_service_req'])
_CENTERMSG.fields_by_name['sync_service_req'].containing_oneof = _CENTERMSG.oneofs_by_name['choice']
_CENTERMSG.oneofs_by_name['choice'].fields.append(
  _CENTERMSG.fields_by_name['sync_service_rsp'])
_CENTERMSG.fields_by_name['sync_service_rsp'].containing_oneof = _CENTERMSG.oneofs_by_name['choice']
DESCRIPTOR.message_types_by_name['CenterMsg'] = _CENTERMSG
DESCRIPTOR.message_types_by_name['HeartbeatReq'] = _HEARTBEATREQ
DESCRIPTOR.message_types_by_name['HeartbeatRsp'] = _HEARTBEATRSP
DESCRIPTOR.message_types_by_name['SyncServiceReq'] = _SYNCSERVICEREQ
DESCRIPTOR.message_types_by_name['SyncServiceRsp'] = _SYNCSERVICERSP
DESCRIPTOR.enum_types_by_name['ErrorCode'] = _ERRORCODE
DESCRIPTOR.enum_types_by_name['State'] = _STATE
DESCRIPTOR.enum_types_by_name['Level'] = _LEVEL

CenterMsg = _reflection.GeneratedProtocolMessageType('CenterMsg', (_message.Message,), dict(
  DESCRIPTOR = _CENTERMSG,
  __module__ = 'center_pb2'
  # @@protoc_insertion_point(class_scope:center.CenterMsg)
  ))
_sym_db.RegisterMessage(CenterMsg)

HeartbeatReq = _reflection.GeneratedProtocolMessageType('HeartbeatReq', (_message.Message,), dict(
  DESCRIPTOR = _HEARTBEATREQ,
  __module__ = 'center_pb2'
  # @@protoc_insertion_point(class_scope:center.HeartbeatReq)
  ))
_sym_db.RegisterMessage(HeartbeatReq)

HeartbeatRsp = _reflection.GeneratedProtocolMessageType('HeartbeatRsp', (_message.Message,), dict(
  DESCRIPTOR = _HEARTBEATRSP,
  __module__ = 'center_pb2'
  # @@protoc_insertion_point(class_scope:center.HeartbeatRsp)
  ))
_sym_db.RegisterMessage(HeartbeatRsp)

SyncServiceReq = _reflection.GeneratedProtocolMessageType('SyncServiceReq', (_message.Message,), dict(
  DESCRIPTOR = _SYNCSERVICEREQ,
  __module__ = 'center_pb2'
  # @@protoc_insertion_point(class_scope:center.SyncServiceReq)
  ))
_sym_db.RegisterMessage(SyncServiceReq)

SyncServiceRsp = _reflection.GeneratedProtocolMessageType('SyncServiceRsp', (_message.Message,), dict(
  DESCRIPTOR = _SYNCSERVICERSP,
  __module__ = 'center_pb2'
  # @@protoc_insertion_point(class_scope:center.SyncServiceRsp)
  ))
_sym_db.RegisterMessage(SyncServiceRsp)


# @@protoc_insertion_point(module_scope)
