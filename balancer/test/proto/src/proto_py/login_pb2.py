# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: login.proto

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
  name='login.proto',
  package='login',
  syntax='proto3',
  serialized_pb=_b('\n\x0blogin.proto\x12\x05login\x1a\x0c\x63ommon.proto\"\x88\x02\n\x08LoginMsg\x12#\n\x08test_req\x18\x01 \x01(\x0b\x32\x0f.common.TestReqH\x00\x12#\n\x08test_rsp\x18\x02 \x01(\x0b\x32\x0f.common.TestRspH\x00\x12$\n\tlogin_req\x18\x03 \x01(\x0b\x32\x0f.login.LoginReqH\x00\x12$\n\tlogin_rsp\x18\x04 \x01(\x0b\x32\x0f.login.LoginRspH\x00\x12-\n\x0e\x61\x63\x63\x65ss_key_req\x18\x05 \x01(\x0b\x32\x13.login.AccessKeyReqH\x00\x12-\n\x0e\x61\x63\x63\x65ss_key_rsp\x18\x06 \x01(\x0b\x32\x13.login.AccessKeyRspH\x00\x42\x08\n\x06\x63hoice\"u\n\x08LoginReq\x12\x12\n\nservice_id\x18\x01 \x01(\x05\x12\x0f\n\x07proc_id\x18\x02 \x01(\r\x12\x0f\n\x07user_id\x18\x03 \x01(\x04\x12\x0e\n\x06passwd\x18\x04 \x01(\x0c\x12\x10\n\x08\x64\x65v_type\x18\x05 \x01(\r\x12\x11\n\tdev_token\x18\x06 \x01(\x0c\"\n\n\x08LoginRsp\"\x0e\n\x0c\x41\x63\x63\x65ssKeyReq\"\"\n\x0c\x41\x63\x63\x65ssKeyRsp\x12\x12\n\naccess_key\x18\x01 \x01(\x0c*\xa6\t\n\tErrorCode\x12\x0b\n\x07SUCCESS\x10\x00\x12\x14\n\rERR_SYS_BEGIN\x10\xa4\xd9\x88\x32\x12\x17\n\x10\x45RR_SYS_OVERLOAD\x10\xa5\xd9\x88\x32\x12\x1d\n\x16\x45RR_SYS_REJECT_SERVICE\x10\xa6\xd9\x88\x32\x12\x1b\n\x14\x45RR_SYS_SERVER_INNER\x10\xa7\xd9\x88\x32\x12\x16\n\x0f\x45RR_SYS_TIMEOUT\x10\xa8\xd9\x88\x32\x12 \n\x19\x45RR_SYS_NO_INSERVICE_LIST\x10\xa9\xd9\x88\x32\x12\x19\n\x12\x45RR_SYS_TASK_STATE\x10\xaa\xd9\x88\x32\x12\x1b\n\x14\x45RR_SYS_TASK_DISCARD\x10\xab\xd9\x88\x32\x12\x12\n\x0b\x45RR_SYS_END\x10\x87\xda\x88\x32\x12\x17\n\x10\x45RR_PACKET_BEGIN\x10\x88\xda\x88\x32\x12\x18\n\x11\x45RR_PACKET_ENCODE\x10\x89\xda\x88\x32\x12\x18\n\x11\x45RR_PACKET_DECODE\x10\x8a\xda\x88\x32\x12\x18\n\x11\x45RR_PACKET_HEADER\x10\x8b\xda\x88\x32\x12\x15\n\x0e\x45RR_PACKET_LEN\x10\x8c\xda\x88\x32\x12\x19\n\x12\x45RR_PACKET_VERSION\x10\x8d\xda\x88\x32\x12!\n\x1a\x45RR_PACKET_FROM_SERVICE_ID\x10\x8e\xda\x88\x32\x12\x1f\n\x18\x45RR_PACKET_TO_SERVICE_ID\x10\x8f\xda\x88\x32\x12\x18\n\x11\x45RR_PACKET_APP_ID\x10\x90\xda\x88\x32\x12\x1d\n\x16\x45RR_PACKET_APP_VERSION\x10\x91\xda\x88\x32\x12\x1d\n\x16\x45RR_PACKET_CONN_SEQ_ID\x10\x92\xda\x88\x32\x12\x1c\n\x15\x45RR_PACKET_MSG_SEQ_ID\x10\x93\xda\x88\x32\x12\x1d\n\x16\x45RR_PACKET_DATA_FORMAT\x10\x94\xda\x88\x32\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_0\x10\x95\xda\x88\x32\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_1\x10\x96\xda\x88\x32\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_2\x10\x97\xda\x88\x32\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_3\x10\x98\xda\x88\x32\x12\x1b\n\x14\x45RR_PACKET_CHECK_SUM\x10\x99\xda\x88\x32\x12!\n\x1a\x45RR_PACKET_UNKNOWN_REQUEST\x10\x9a\xda\x88\x32\x12\x15\n\x0e\x45RR_PACKET_END\x10\xeb\xda\x88\x32\x12\x1a\n\x13\x45RR_INTERFACE_BEGIN\x10\xec\xda\x88\x32\x12\x1a\n\x13\x45RR_INTERFACE_PARAM\x10\xed\xda\x88\x32\x12\x19\n\x12\x45RR_INTERFACE_PERM\x10\xee\xda\x88\x32\x12\x1c\n\x15\x45RR_INTERFACE_TIMEOUT\x10\xef\xda\x88\x32\x12#\n\x1c\x45RR_INTERFACE_MASTER_TIMEOUT\x10\xf0\xda\x88\x32\x12 \n\x19\x45RR_INTERFACE_SUB_TIMEOUT\x10\xf1\xda\x88\x32\x12\x18\n\x11\x45RR_INTERFACE_END\x10\xcf\xdb\x88\x32\x12\x19\n\x12\x45RR_BUSINESS_BEGIN\x10\xa8\xe0\x88\x32\x12$\n\x1d\x45RR_BUSINESS_ACCESS_KEY_ERROR\x10\xa9\xe0\x88\x32\x12&\n\x1f\x45RR_BUSINESS_ACCESS_KEY_TIMEOUT\x10\xaa\xe0\x88\x32\x12\x17\n\x10\x45RR_BUSINESS_END\x10\xcf\xa6\x89\x32\x62\x06proto3')
  ,
  dependencies=[common__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

_ERRORCODE = _descriptor.EnumDescriptor(
  name='ErrorCode',
  full_name='login.ErrorCode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SUCCESS', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_BEGIN', index=1, number=105000100,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_OVERLOAD', index=2, number=105000101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_REJECT_SERVICE', index=3, number=105000102,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_SERVER_INNER', index=4, number=105000103,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TIMEOUT', index=5, number=105000104,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_NO_INSERVICE_LIST', index=6, number=105000105,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TASK_STATE', index=7, number=105000106,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TASK_DISCARD', index=8, number=105000107,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_END', index=9, number=105000199,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_BEGIN', index=10, number=105000200,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_ENCODE', index=11, number=105000201,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DECODE', index=12, number=105000202,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_HEADER', index=13, number=105000203,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_LEN', index=14, number=105000204,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_VERSION', index=15, number=105000205,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_FROM_SERVICE_ID', index=16, number=105000206,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_TO_SERVICE_ID', index=17, number=105000207,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_APP_ID', index=18, number=105000208,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_APP_VERSION', index=19, number=105000209,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_CONN_SEQ_ID', index=20, number=105000210,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_MSG_SEQ_ID', index=21, number=105000211,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FORMAT', index=22, number=105000212,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_0', index=23, number=105000213,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_1', index=24, number=105000214,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_2', index=25, number=105000215,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_3', index=26, number=105000216,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_CHECK_SUM', index=27, number=105000217,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_UNKNOWN_REQUEST', index=28, number=105000218,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_END', index=29, number=105000299,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_BEGIN', index=30, number=105000300,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_PARAM', index=31, number=105000301,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_PERM', index=32, number=105000302,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_TIMEOUT', index=33, number=105000303,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_MASTER_TIMEOUT', index=34, number=105000304,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_SUB_TIMEOUT', index=35, number=105000305,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_END', index=36, number=105000399,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_BEGIN', index=37, number=105001000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_ACCESS_KEY_ERROR', index=38, number=105001001,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_ACCESS_KEY_TIMEOUT', index=39, number=105001002,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_END', index=40, number=105009999,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=487,
  serialized_end=1677,
)
_sym_db.RegisterEnumDescriptor(_ERRORCODE)

ErrorCode = enum_type_wrapper.EnumTypeWrapper(_ERRORCODE)
SUCCESS = 0
ERR_SYS_BEGIN = 105000100
ERR_SYS_OVERLOAD = 105000101
ERR_SYS_REJECT_SERVICE = 105000102
ERR_SYS_SERVER_INNER = 105000103
ERR_SYS_TIMEOUT = 105000104
ERR_SYS_NO_INSERVICE_LIST = 105000105
ERR_SYS_TASK_STATE = 105000106
ERR_SYS_TASK_DISCARD = 105000107
ERR_SYS_END = 105000199
ERR_PACKET_BEGIN = 105000200
ERR_PACKET_ENCODE = 105000201
ERR_PACKET_DECODE = 105000202
ERR_PACKET_HEADER = 105000203
ERR_PACKET_LEN = 105000204
ERR_PACKET_VERSION = 105000205
ERR_PACKET_FROM_SERVICE_ID = 105000206
ERR_PACKET_TO_SERVICE_ID = 105000207
ERR_PACKET_APP_ID = 105000208
ERR_PACKET_APP_VERSION = 105000209
ERR_PACKET_CONN_SEQ_ID = 105000210
ERR_PACKET_MSG_SEQ_ID = 105000211
ERR_PACKET_DATA_FORMAT = 105000212
ERR_PACKET_DATA_FIELD_0 = 105000213
ERR_PACKET_DATA_FIELD_1 = 105000214
ERR_PACKET_DATA_FIELD_2 = 105000215
ERR_PACKET_DATA_FIELD_3 = 105000216
ERR_PACKET_CHECK_SUM = 105000217
ERR_PACKET_UNKNOWN_REQUEST = 105000218
ERR_PACKET_END = 105000299
ERR_INTERFACE_BEGIN = 105000300
ERR_INTERFACE_PARAM = 105000301
ERR_INTERFACE_PERM = 105000302
ERR_INTERFACE_TIMEOUT = 105000303
ERR_INTERFACE_MASTER_TIMEOUT = 105000304
ERR_INTERFACE_SUB_TIMEOUT = 105000305
ERR_INTERFACE_END = 105000399
ERR_BUSINESS_BEGIN = 105001000
ERR_BUSINESS_ACCESS_KEY_ERROR = 105001001
ERR_BUSINESS_ACCESS_KEY_TIMEOUT = 105001002
ERR_BUSINESS_END = 105009999



_LOGINMSG = _descriptor.Descriptor(
  name='LoginMsg',
  full_name='login.LoginMsg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='test_req', full_name='login.LoginMsg.test_req', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='test_rsp', full_name='login.LoginMsg.test_rsp', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='login_req', full_name='login.LoginMsg.login_req', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='login_rsp', full_name='login.LoginMsg.login_rsp', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='access_key_req', full_name='login.LoginMsg.access_key_req', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='access_key_rsp', full_name='login.LoginMsg.access_key_rsp', index=5,
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
      name='choice', full_name='login.LoginMsg.choice',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=37,
  serialized_end=301,
)


_LOGINREQ = _descriptor.Descriptor(
  name='LoginReq',
  full_name='login.LoginReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='service_id', full_name='login.LoginReq.service_id', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='proc_id', full_name='login.LoginReq.proc_id', index=1,
      number=2, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='user_id', full_name='login.LoginReq.user_id', index=2,
      number=3, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='passwd', full_name='login.LoginReq.passwd', index=3,
      number=4, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dev_type', full_name='login.LoginReq.dev_type', index=4,
      number=5, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='dev_token', full_name='login.LoginReq.dev_token', index=5,
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
  serialized_start=303,
  serialized_end=420,
)


_LOGINRSP = _descriptor.Descriptor(
  name='LoginRsp',
  full_name='login.LoginRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
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
  serialized_start=422,
  serialized_end=432,
)


_ACCESSKEYREQ = _descriptor.Descriptor(
  name='AccessKeyReq',
  full_name='login.AccessKeyReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
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
  serialized_start=434,
  serialized_end=448,
)


_ACCESSKEYRSP = _descriptor.Descriptor(
  name='AccessKeyRsp',
  full_name='login.AccessKeyRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='access_key', full_name='login.AccessKeyRsp.access_key', index=0,
      number=1, type=12, cpp_type=9, label=1,
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
  serialized_start=450,
  serialized_end=484,
)

_LOGINMSG.fields_by_name['test_req'].message_type = common__pb2._TESTREQ
_LOGINMSG.fields_by_name['test_rsp'].message_type = common__pb2._TESTRSP
_LOGINMSG.fields_by_name['login_req'].message_type = _LOGINREQ
_LOGINMSG.fields_by_name['login_rsp'].message_type = _LOGINRSP
_LOGINMSG.fields_by_name['access_key_req'].message_type = _ACCESSKEYREQ
_LOGINMSG.fields_by_name['access_key_rsp'].message_type = _ACCESSKEYRSP
_LOGINMSG.oneofs_by_name['choice'].fields.append(
  _LOGINMSG.fields_by_name['test_req'])
_LOGINMSG.fields_by_name['test_req'].containing_oneof = _LOGINMSG.oneofs_by_name['choice']
_LOGINMSG.oneofs_by_name['choice'].fields.append(
  _LOGINMSG.fields_by_name['test_rsp'])
_LOGINMSG.fields_by_name['test_rsp'].containing_oneof = _LOGINMSG.oneofs_by_name['choice']
_LOGINMSG.oneofs_by_name['choice'].fields.append(
  _LOGINMSG.fields_by_name['login_req'])
_LOGINMSG.fields_by_name['login_req'].containing_oneof = _LOGINMSG.oneofs_by_name['choice']
_LOGINMSG.oneofs_by_name['choice'].fields.append(
  _LOGINMSG.fields_by_name['login_rsp'])
_LOGINMSG.fields_by_name['login_rsp'].containing_oneof = _LOGINMSG.oneofs_by_name['choice']
_LOGINMSG.oneofs_by_name['choice'].fields.append(
  _LOGINMSG.fields_by_name['access_key_req'])
_LOGINMSG.fields_by_name['access_key_req'].containing_oneof = _LOGINMSG.oneofs_by_name['choice']
_LOGINMSG.oneofs_by_name['choice'].fields.append(
  _LOGINMSG.fields_by_name['access_key_rsp'])
_LOGINMSG.fields_by_name['access_key_rsp'].containing_oneof = _LOGINMSG.oneofs_by_name['choice']
DESCRIPTOR.message_types_by_name['LoginMsg'] = _LOGINMSG
DESCRIPTOR.message_types_by_name['LoginReq'] = _LOGINREQ
DESCRIPTOR.message_types_by_name['LoginRsp'] = _LOGINRSP
DESCRIPTOR.message_types_by_name['AccessKeyReq'] = _ACCESSKEYREQ
DESCRIPTOR.message_types_by_name['AccessKeyRsp'] = _ACCESSKEYRSP
DESCRIPTOR.enum_types_by_name['ErrorCode'] = _ERRORCODE

LoginMsg = _reflection.GeneratedProtocolMessageType('LoginMsg', (_message.Message,), dict(
  DESCRIPTOR = _LOGINMSG,
  __module__ = 'login_pb2'
  # @@protoc_insertion_point(class_scope:login.LoginMsg)
  ))
_sym_db.RegisterMessage(LoginMsg)

LoginReq = _reflection.GeneratedProtocolMessageType('LoginReq', (_message.Message,), dict(
  DESCRIPTOR = _LOGINREQ,
  __module__ = 'login_pb2'
  # @@protoc_insertion_point(class_scope:login.LoginReq)
  ))
_sym_db.RegisterMessage(LoginReq)

LoginRsp = _reflection.GeneratedProtocolMessageType('LoginRsp', (_message.Message,), dict(
  DESCRIPTOR = _LOGINRSP,
  __module__ = 'login_pb2'
  # @@protoc_insertion_point(class_scope:login.LoginRsp)
  ))
_sym_db.RegisterMessage(LoginRsp)

AccessKeyReq = _reflection.GeneratedProtocolMessageType('AccessKeyReq', (_message.Message,), dict(
  DESCRIPTOR = _ACCESSKEYREQ,
  __module__ = 'login_pb2'
  # @@protoc_insertion_point(class_scope:login.AccessKeyReq)
  ))
_sym_db.RegisterMessage(AccessKeyReq)

AccessKeyRsp = _reflection.GeneratedProtocolMessageType('AccessKeyRsp', (_message.Message,), dict(
  DESCRIPTOR = _ACCESSKEYRSP,
  __module__ = 'login_pb2'
  # @@protoc_insertion_point(class_scope:login.AccessKeyRsp)
  ))
_sym_db.RegisterMessage(AccessKeyRsp)


# @@protoc_insertion_point(module_scope)
