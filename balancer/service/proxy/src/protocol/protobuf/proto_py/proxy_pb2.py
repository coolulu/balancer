# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: proxy.proto

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
  name='proxy.proto',
  package='proxy',
  syntax='proto3',
  serialized_pb=_b('\n\x0bproxy.proto\x12\x05proxy\x1a\x0c\x63ommon.proto\"\xac\x02\n\x08ProxyMsg\x12#\n\x08test_req\x18\x01 \x01(\x0b\x32\x0f.common.TestReqH\x00\x12#\n\x08test_rsp\x18\x02 \x01(\x0b\x32\x0f.common.TestRspH\x00\x12\x32\n\x11get_user_info_req\x18\x03 \x01(\x0b\x32\x15.proxy.GetUserInfoReqH\x00\x12\x32\n\x11get_user_info_rsp\x18\x04 \x01(\x0b\x32\x15.proxy.GetUserInfoRspH\x00\x12\x31\n\x10\x63heck_passwd_req\x18\x05 \x01(\x0b\x32\x15.proxy.CheckPasswdReqH\x00\x12\x31\n\x10\x63heck_passwd_rsp\x18\x06 \x01(\x0b\x32\x15.proxy.CheckPasswdRspH\x00\x42\x08\n\x06\x63hoice\"!\n\x0eGetUserInfoReq\x12\x0f\n\x07user_id\x18\x01 \x01(\x04\"\x10\n\x0eGetUserInfoRsp\"1\n\x0e\x43heckPasswdReq\x12\x0f\n\x07user_id\x18\x01 \x01(\x04\x12\x0e\n\x06passwd\x18\x02 \x01(\x0c\"\x10\n\x0e\x43heckPasswdRsp*\xce\t\n\tErrorCode\x12\x0b\n\x07SUCCESS\x10\x00\x12\x15\n\rERR_SYS_BEGIN\x10\xa4\xcb\xc3\x8f\x01\x12\x18\n\x10\x45RR_SYS_OVERLOAD\x10\xa5\xcb\xc3\x8f\x01\x12\x1e\n\x16\x45RR_SYS_REJECT_SERVICE\x10\xa6\xcb\xc3\x8f\x01\x12\x1c\n\x14\x45RR_SYS_SERVER_INNER\x10\xa7\xcb\xc3\x8f\x01\x12\x17\n\x0f\x45RR_SYS_TIMEOUT\x10\xa8\xcb\xc3\x8f\x01\x12!\n\x19\x45RR_SYS_NO_INSERVICE_LIST\x10\xa9\xcb\xc3\x8f\x01\x12\x1a\n\x12\x45RR_SYS_TASK_STATE\x10\xaa\xcb\xc3\x8f\x01\x12\x1c\n\x14\x45RR_SYS_TASK_DISCARD\x10\xab\xcb\xc3\x8f\x01\x12\x13\n\x0b\x45RR_SYS_END\x10\x87\xcc\xc3\x8f\x01\x12\x18\n\x10\x45RR_PACKET_BEGIN\x10\x88\xcc\xc3\x8f\x01\x12\x19\n\x11\x45RR_PACKET_ENCODE\x10\x89\xcc\xc3\x8f\x01\x12\x19\n\x11\x45RR_PACKET_DECODE\x10\x8a\xcc\xc3\x8f\x01\x12\x19\n\x11\x45RR_PACKET_HEADER\x10\x8b\xcc\xc3\x8f\x01\x12\x16\n\x0e\x45RR_PACKET_LEN\x10\x8c\xcc\xc3\x8f\x01\x12\x1a\n\x12\x45RR_PACKET_VERSION\x10\x8d\xcc\xc3\x8f\x01\x12\"\n\x1a\x45RR_PACKET_FROM_SERVICE_ID\x10\x8e\xcc\xc3\x8f\x01\x12 \n\x18\x45RR_PACKET_TO_SERVICE_ID\x10\x8f\xcc\xc3\x8f\x01\x12\x19\n\x11\x45RR_PACKET_APP_ID\x10\x90\xcc\xc3\x8f\x01\x12\x1e\n\x16\x45RR_PACKET_APP_VERSION\x10\x91\xcc\xc3\x8f\x01\x12\x1e\n\x16\x45RR_PACKET_CONN_SEQ_ID\x10\x92\xcc\xc3\x8f\x01\x12\x1d\n\x15\x45RR_PACKET_MSG_SEQ_ID\x10\x93\xcc\xc3\x8f\x01\x12\x1e\n\x16\x45RR_PACKET_DATA_FORMAT\x10\x94\xcc\xc3\x8f\x01\x12\x1f\n\x17\x45RR_PACKET_DATA_FIELD_0\x10\x95\xcc\xc3\x8f\x01\x12\x1f\n\x17\x45RR_PACKET_DATA_FIELD_1\x10\x96\xcc\xc3\x8f\x01\x12\x1f\n\x17\x45RR_PACKET_DATA_FIELD_2\x10\x97\xcc\xc3\x8f\x01\x12\x1f\n\x17\x45RR_PACKET_DATA_FIELD_3\x10\x98\xcc\xc3\x8f\x01\x12\x1c\n\x14\x45RR_PACKET_CHECK_SUM\x10\x99\xcc\xc3\x8f\x01\x12\"\n\x1a\x45RR_PACKET_UNKNOWN_REQUEST\x10\x9a\xcc\xc3\x8f\x01\x12\x16\n\x0e\x45RR_PACKET_END\x10\xeb\xcc\xc3\x8f\x01\x12\x1b\n\x13\x45RR_INTERFACE_BEGIN\x10\xec\xcc\xc3\x8f\x01\x12\x1b\n\x13\x45RR_INTERFACE_PARAM\x10\xed\xcc\xc3\x8f\x01\x12\x1a\n\x12\x45RR_INTERFACE_PERM\x10\xee\xcc\xc3\x8f\x01\x12\x1d\n\x15\x45RR_INTERFACE_TIMEOUT\x10\xef\xcc\xc3\x8f\x01\x12$\n\x1c\x45RR_INTERFACE_MASTER_TIMEOUT\x10\xf0\xcc\xc3\x8f\x01\x12!\n\x19\x45RR_INTERFACE_SUB_TIMEOUT\x10\xf1\xcc\xc3\x8f\x01\x12\x19\n\x11\x45RR_INTERFACE_END\x10\xcf\xcd\xc3\x8f\x01\x12\x1a\n\x12\x45RR_BUSINESS_BEGIN\x10\xa8\xd2\xc3\x8f\x01\x12%\n\x1d\x45RR_BUSINESS_NOT_FIND_USER_ID\x10\xa9\xd2\xc3\x8f\x01\x12\'\n\x1f\x45RR_BUSINESS_CHECK_PASSWD_ERROR\x10\xaa\xd2\xc3\x8f\x01\x12\x18\n\x10\x45RR_BUSINESS_END\x10\xcf\x98\xc4\x8f\x01\x62\x06proto3')
  ,
  dependencies=[common__pb2.DESCRIPTOR,])

_ERRORCODE = _descriptor.EnumDescriptor(
  name='ErrorCode',
  full_name='proxy.ErrorCode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SUCCESS', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_BEGIN', index=1, number=301000100,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_OVERLOAD', index=2, number=301000101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_REJECT_SERVICE', index=3, number=301000102,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_SERVER_INNER', index=4, number=301000103,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TIMEOUT', index=5, number=301000104,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_NO_INSERVICE_LIST', index=6, number=301000105,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TASK_STATE', index=7, number=301000106,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TASK_DISCARD', index=8, number=301000107,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_END', index=9, number=301000199,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_BEGIN', index=10, number=301000200,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_ENCODE', index=11, number=301000201,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DECODE', index=12, number=301000202,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_HEADER', index=13, number=301000203,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_LEN', index=14, number=301000204,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_VERSION', index=15, number=301000205,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_FROM_SERVICE_ID', index=16, number=301000206,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_TO_SERVICE_ID', index=17, number=301000207,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_APP_ID', index=18, number=301000208,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_APP_VERSION', index=19, number=301000209,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_CONN_SEQ_ID', index=20, number=301000210,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_MSG_SEQ_ID', index=21, number=301000211,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FORMAT', index=22, number=301000212,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_0', index=23, number=301000213,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_1', index=24, number=301000214,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_2', index=25, number=301000215,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_3', index=26, number=301000216,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_CHECK_SUM', index=27, number=301000217,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_UNKNOWN_REQUEST', index=28, number=301000218,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_END', index=29, number=301000299,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_BEGIN', index=30, number=301000300,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_PARAM', index=31, number=301000301,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_PERM', index=32, number=301000302,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_TIMEOUT', index=33, number=301000303,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_MASTER_TIMEOUT', index=34, number=301000304,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_SUB_TIMEOUT', index=35, number=301000305,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_END', index=36, number=301000399,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_BEGIN', index=37, number=301001000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_NOT_FIND_USER_ID', index=38, number=301001001,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_CHECK_PASSWD_ERROR', index=39, number=301001002,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_END', index=40, number=301009999,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=462,
  serialized_end=1692,
)
_sym_db.RegisterEnumDescriptor(_ERRORCODE)

ErrorCode = enum_type_wrapper.EnumTypeWrapper(_ERRORCODE)
SUCCESS = 0
ERR_SYS_BEGIN = 301000100
ERR_SYS_OVERLOAD = 301000101
ERR_SYS_REJECT_SERVICE = 301000102
ERR_SYS_SERVER_INNER = 301000103
ERR_SYS_TIMEOUT = 301000104
ERR_SYS_NO_INSERVICE_LIST = 301000105
ERR_SYS_TASK_STATE = 301000106
ERR_SYS_TASK_DISCARD = 301000107
ERR_SYS_END = 301000199
ERR_PACKET_BEGIN = 301000200
ERR_PACKET_ENCODE = 301000201
ERR_PACKET_DECODE = 301000202
ERR_PACKET_HEADER = 301000203
ERR_PACKET_LEN = 301000204
ERR_PACKET_VERSION = 301000205
ERR_PACKET_FROM_SERVICE_ID = 301000206
ERR_PACKET_TO_SERVICE_ID = 301000207
ERR_PACKET_APP_ID = 301000208
ERR_PACKET_APP_VERSION = 301000209
ERR_PACKET_CONN_SEQ_ID = 301000210
ERR_PACKET_MSG_SEQ_ID = 301000211
ERR_PACKET_DATA_FORMAT = 301000212
ERR_PACKET_DATA_FIELD_0 = 301000213
ERR_PACKET_DATA_FIELD_1 = 301000214
ERR_PACKET_DATA_FIELD_2 = 301000215
ERR_PACKET_DATA_FIELD_3 = 301000216
ERR_PACKET_CHECK_SUM = 301000217
ERR_PACKET_UNKNOWN_REQUEST = 301000218
ERR_PACKET_END = 301000299
ERR_INTERFACE_BEGIN = 301000300
ERR_INTERFACE_PARAM = 301000301
ERR_INTERFACE_PERM = 301000302
ERR_INTERFACE_TIMEOUT = 301000303
ERR_INTERFACE_MASTER_TIMEOUT = 301000304
ERR_INTERFACE_SUB_TIMEOUT = 301000305
ERR_INTERFACE_END = 301000399
ERR_BUSINESS_BEGIN = 301001000
ERR_BUSINESS_NOT_FIND_USER_ID = 301001001
ERR_BUSINESS_CHECK_PASSWD_ERROR = 301001002
ERR_BUSINESS_END = 301009999



_PROXYMSG = _descriptor.Descriptor(
  name='ProxyMsg',
  full_name='proxy.ProxyMsg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='test_req', full_name='proxy.ProxyMsg.test_req', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='test_rsp', full_name='proxy.ProxyMsg.test_rsp', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='get_user_info_req', full_name='proxy.ProxyMsg.get_user_info_req', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='get_user_info_rsp', full_name='proxy.ProxyMsg.get_user_info_rsp', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='check_passwd_req', full_name='proxy.ProxyMsg.check_passwd_req', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='check_passwd_rsp', full_name='proxy.ProxyMsg.check_passwd_rsp', index=5,
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
      name='choice', full_name='proxy.ProxyMsg.choice',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=37,
  serialized_end=337,
)


_GETUSERINFOREQ = _descriptor.Descriptor(
  name='GetUserInfoReq',
  full_name='proxy.GetUserInfoReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='proxy.GetUserInfoReq.user_id', index=0,
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
  serialized_start=339,
  serialized_end=372,
)


_GETUSERINFORSP = _descriptor.Descriptor(
  name='GetUserInfoRsp',
  full_name='proxy.GetUserInfoRsp',
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
  serialized_start=374,
  serialized_end=390,
)


_CHECKPASSWDREQ = _descriptor.Descriptor(
  name='CheckPasswdReq',
  full_name='proxy.CheckPasswdReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='user_id', full_name='proxy.CheckPasswdReq.user_id', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='passwd', full_name='proxy.CheckPasswdReq.passwd', index=1,
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
  serialized_start=392,
  serialized_end=441,
)


_CHECKPASSWDRSP = _descriptor.Descriptor(
  name='CheckPasswdRsp',
  full_name='proxy.CheckPasswdRsp',
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
  serialized_start=443,
  serialized_end=459,
)

_PROXYMSG.fields_by_name['test_req'].message_type = common__pb2._TESTREQ
_PROXYMSG.fields_by_name['test_rsp'].message_type = common__pb2._TESTRSP
_PROXYMSG.fields_by_name['get_user_info_req'].message_type = _GETUSERINFOREQ
_PROXYMSG.fields_by_name['get_user_info_rsp'].message_type = _GETUSERINFORSP
_PROXYMSG.fields_by_name['check_passwd_req'].message_type = _CHECKPASSWDREQ
_PROXYMSG.fields_by_name['check_passwd_rsp'].message_type = _CHECKPASSWDRSP
_PROXYMSG.oneofs_by_name['choice'].fields.append(
  _PROXYMSG.fields_by_name['test_req'])
_PROXYMSG.fields_by_name['test_req'].containing_oneof = _PROXYMSG.oneofs_by_name['choice']
_PROXYMSG.oneofs_by_name['choice'].fields.append(
  _PROXYMSG.fields_by_name['test_rsp'])
_PROXYMSG.fields_by_name['test_rsp'].containing_oneof = _PROXYMSG.oneofs_by_name['choice']
_PROXYMSG.oneofs_by_name['choice'].fields.append(
  _PROXYMSG.fields_by_name['get_user_info_req'])
_PROXYMSG.fields_by_name['get_user_info_req'].containing_oneof = _PROXYMSG.oneofs_by_name['choice']
_PROXYMSG.oneofs_by_name['choice'].fields.append(
  _PROXYMSG.fields_by_name['get_user_info_rsp'])
_PROXYMSG.fields_by_name['get_user_info_rsp'].containing_oneof = _PROXYMSG.oneofs_by_name['choice']
_PROXYMSG.oneofs_by_name['choice'].fields.append(
  _PROXYMSG.fields_by_name['check_passwd_req'])
_PROXYMSG.fields_by_name['check_passwd_req'].containing_oneof = _PROXYMSG.oneofs_by_name['choice']
_PROXYMSG.oneofs_by_name['choice'].fields.append(
  _PROXYMSG.fields_by_name['check_passwd_rsp'])
_PROXYMSG.fields_by_name['check_passwd_rsp'].containing_oneof = _PROXYMSG.oneofs_by_name['choice']
DESCRIPTOR.message_types_by_name['ProxyMsg'] = _PROXYMSG
DESCRIPTOR.message_types_by_name['GetUserInfoReq'] = _GETUSERINFOREQ
DESCRIPTOR.message_types_by_name['GetUserInfoRsp'] = _GETUSERINFORSP
DESCRIPTOR.message_types_by_name['CheckPasswdReq'] = _CHECKPASSWDREQ
DESCRIPTOR.message_types_by_name['CheckPasswdRsp'] = _CHECKPASSWDRSP
DESCRIPTOR.enum_types_by_name['ErrorCode'] = _ERRORCODE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

ProxyMsg = _reflection.GeneratedProtocolMessageType('ProxyMsg', (_message.Message,), dict(
  DESCRIPTOR = _PROXYMSG,
  __module__ = 'proxy_pb2'
  # @@protoc_insertion_point(class_scope:proxy.ProxyMsg)
  ))
_sym_db.RegisterMessage(ProxyMsg)

GetUserInfoReq = _reflection.GeneratedProtocolMessageType('GetUserInfoReq', (_message.Message,), dict(
  DESCRIPTOR = _GETUSERINFOREQ,
  __module__ = 'proxy_pb2'
  # @@protoc_insertion_point(class_scope:proxy.GetUserInfoReq)
  ))
_sym_db.RegisterMessage(GetUserInfoReq)

GetUserInfoRsp = _reflection.GeneratedProtocolMessageType('GetUserInfoRsp', (_message.Message,), dict(
  DESCRIPTOR = _GETUSERINFORSP,
  __module__ = 'proxy_pb2'
  # @@protoc_insertion_point(class_scope:proxy.GetUserInfoRsp)
  ))
_sym_db.RegisterMessage(GetUserInfoRsp)

CheckPasswdReq = _reflection.GeneratedProtocolMessageType('CheckPasswdReq', (_message.Message,), dict(
  DESCRIPTOR = _CHECKPASSWDREQ,
  __module__ = 'proxy_pb2'
  # @@protoc_insertion_point(class_scope:proxy.CheckPasswdReq)
  ))
_sym_db.RegisterMessage(CheckPasswdReq)

CheckPasswdRsp = _reflection.GeneratedProtocolMessageType('CheckPasswdRsp', (_message.Message,), dict(
  DESCRIPTOR = _CHECKPASSWDRSP,
  __module__ = 'proxy_pb2'
  # @@protoc_insertion_point(class_scope:proxy.CheckPasswdRsp)
  ))
_sym_db.RegisterMessage(CheckPasswdRsp)


# @@protoc_insertion_point(module_scope)
