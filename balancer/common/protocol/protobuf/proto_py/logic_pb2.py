# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: logic.proto

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
  name='logic.proto',
  package='logic',
  syntax='proto3',
  serialized_pb=_b('\n\x0blogic.proto\x12\x05logic\x1a\x0c\x63ommon.proto\"^\n\x08LogicMsg\x12#\n\x08test_req\x18\x01 \x01(\x0b\x32\x0f.common.TestReqH\x00\x12#\n\x08test_rsp\x18\x02 \x01(\x0b\x32\x0f.common.TestRspH\x00\x42\x08\n\x06\x63hoice*\xd8\x08\n\tErrorCode\x12\x0b\n\x07SUCCESS\x10\x00\x12\x14\n\rERR_SYS_BEGIN\x10\xa4\x89\xec_\x12\x17\n\x10\x45RR_SYS_OVERLOAD\x10\xa5\x89\xec_\x12\x1d\n\x16\x45RR_SYS_REJECT_SERVICE\x10\xa6\x89\xec_\x12\x1b\n\x14\x45RR_SYS_SERVER_INNER\x10\xa7\x89\xec_\x12\x16\n\x0f\x45RR_SYS_TIMEOUT\x10\xa8\x89\xec_\x12 \n\x19\x45RR_SYS_NO_INSERVICE_LIST\x10\xa9\x89\xec_\x12\x19\n\x12\x45RR_SYS_TASK_STATE\x10\xaa\x89\xec_\x12\x1b\n\x14\x45RR_SYS_TASK_DISCARD\x10\xab\x89\xec_\x12\x12\n\x0b\x45RR_SYS_END\x10\x87\x8a\xec_\x12\x17\n\x10\x45RR_PACKET_BEGIN\x10\x88\x8a\xec_\x12\x18\n\x11\x45RR_PACKET_ENCODE\x10\x89\x8a\xec_\x12\x18\n\x11\x45RR_PACKET_DECODE\x10\x8a\x8a\xec_\x12\x18\n\x11\x45RR_PACKET_HEADER\x10\x8b\x8a\xec_\x12\x15\n\x0e\x45RR_PACKET_LEN\x10\x8c\x8a\xec_\x12\x19\n\x12\x45RR_PACKET_VERSION\x10\x8d\x8a\xec_\x12!\n\x1a\x45RR_PACKET_FROM_SERVICE_ID\x10\x8e\x8a\xec_\x12\x1f\n\x18\x45RR_PACKET_TO_SERVICE_ID\x10\x8f\x8a\xec_\x12\x18\n\x11\x45RR_PACKET_APP_ID\x10\x90\x8a\xec_\x12\x1d\n\x16\x45RR_PACKET_APP_VERSION\x10\x91\x8a\xec_\x12\x1d\n\x16\x45RR_PACKET_CONN_SEQ_ID\x10\x92\x8a\xec_\x12\x1c\n\x15\x45RR_PACKET_MSG_SEQ_ID\x10\x93\x8a\xec_\x12\x1d\n\x16\x45RR_PACKET_DATA_FORMAT\x10\x94\x8a\xec_\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_0\x10\x95\x8a\xec_\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_1\x10\x96\x8a\xec_\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_2\x10\x97\x8a\xec_\x12\x1e\n\x17\x45RR_PACKET_DATA_FIELD_3\x10\x98\x8a\xec_\x12\x1b\n\x14\x45RR_PACKET_CHECK_SUM\x10\x99\x8a\xec_\x12!\n\x1a\x45RR_PACKET_UNKNOWN_REQUEST\x10\x9a\x8a\xec_\x12\x15\n\x0e\x45RR_PACKET_END\x10\xeb\x8a\xec_\x12\x1a\n\x13\x45RR_INTERFACE_BEGIN\x10\xec\x8a\xec_\x12\x1a\n\x13\x45RR_INTERFACE_PARAM\x10\xed\x8a\xec_\x12\x19\n\x12\x45RR_INTERFACE_PERM\x10\xee\x8a\xec_\x12\x1c\n\x15\x45RR_INTERFACE_TIMEOUT\x10\xef\x8a\xec_\x12#\n\x1c\x45RR_INTERFACE_MASTER_TIMEOUT\x10\xf0\x8a\xec_\x12 \n\x19\x45RR_INTERFACE_SUB_TIMEOUT\x10\xf1\x8a\xec_\x12\x18\n\x11\x45RR_INTERFACE_END\x10\xcf\x8b\xec_\x12\x19\n\x12\x45RR_BUSINESS_BEGIN\x10\xa8\x90\xec_\x12\x17\n\x10\x45RR_BUSINESS_END\x10\xcf\xd6\xec_b\x06proto3')
  ,
  dependencies=[common__pb2.DESCRIPTOR,])

_ERRORCODE = _descriptor.EnumDescriptor(
  name='ErrorCode',
  full_name='logic.ErrorCode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SUCCESS', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_BEGIN', index=1, number=201000100,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_OVERLOAD', index=2, number=201000101,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_REJECT_SERVICE', index=3, number=201000102,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_SERVER_INNER', index=4, number=201000103,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TIMEOUT', index=5, number=201000104,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_NO_INSERVICE_LIST', index=6, number=201000105,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TASK_STATE', index=7, number=201000106,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_TASK_DISCARD', index=8, number=201000107,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_SYS_END', index=9, number=201000199,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_BEGIN', index=10, number=201000200,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_ENCODE', index=11, number=201000201,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DECODE', index=12, number=201000202,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_HEADER', index=13, number=201000203,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_LEN', index=14, number=201000204,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_VERSION', index=15, number=201000205,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_FROM_SERVICE_ID', index=16, number=201000206,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_TO_SERVICE_ID', index=17, number=201000207,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_APP_ID', index=18, number=201000208,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_APP_VERSION', index=19, number=201000209,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_CONN_SEQ_ID', index=20, number=201000210,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_MSG_SEQ_ID', index=21, number=201000211,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FORMAT', index=22, number=201000212,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_0', index=23, number=201000213,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_1', index=24, number=201000214,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_2', index=25, number=201000215,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_DATA_FIELD_3', index=26, number=201000216,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_CHECK_SUM', index=27, number=201000217,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_UNKNOWN_REQUEST', index=28, number=201000218,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_PACKET_END', index=29, number=201000299,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_BEGIN', index=30, number=201000300,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_PARAM', index=31, number=201000301,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_PERM', index=32, number=201000302,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_TIMEOUT', index=33, number=201000303,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_MASTER_TIMEOUT', index=34, number=201000304,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_SUB_TIMEOUT', index=35, number=201000305,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_INTERFACE_END', index=36, number=201000399,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_BEGIN', index=37, number=201001000,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ERR_BUSINESS_END', index=38, number=201009999,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=133,
  serialized_end=1245,
)
_sym_db.RegisterEnumDescriptor(_ERRORCODE)

ErrorCode = enum_type_wrapper.EnumTypeWrapper(_ERRORCODE)
SUCCESS = 0
ERR_SYS_BEGIN = 201000100
ERR_SYS_OVERLOAD = 201000101
ERR_SYS_REJECT_SERVICE = 201000102
ERR_SYS_SERVER_INNER = 201000103
ERR_SYS_TIMEOUT = 201000104
ERR_SYS_NO_INSERVICE_LIST = 201000105
ERR_SYS_TASK_STATE = 201000106
ERR_SYS_TASK_DISCARD = 201000107
ERR_SYS_END = 201000199
ERR_PACKET_BEGIN = 201000200
ERR_PACKET_ENCODE = 201000201
ERR_PACKET_DECODE = 201000202
ERR_PACKET_HEADER = 201000203
ERR_PACKET_LEN = 201000204
ERR_PACKET_VERSION = 201000205
ERR_PACKET_FROM_SERVICE_ID = 201000206
ERR_PACKET_TO_SERVICE_ID = 201000207
ERR_PACKET_APP_ID = 201000208
ERR_PACKET_APP_VERSION = 201000209
ERR_PACKET_CONN_SEQ_ID = 201000210
ERR_PACKET_MSG_SEQ_ID = 201000211
ERR_PACKET_DATA_FORMAT = 201000212
ERR_PACKET_DATA_FIELD_0 = 201000213
ERR_PACKET_DATA_FIELD_1 = 201000214
ERR_PACKET_DATA_FIELD_2 = 201000215
ERR_PACKET_DATA_FIELD_3 = 201000216
ERR_PACKET_CHECK_SUM = 201000217
ERR_PACKET_UNKNOWN_REQUEST = 201000218
ERR_PACKET_END = 201000299
ERR_INTERFACE_BEGIN = 201000300
ERR_INTERFACE_PARAM = 201000301
ERR_INTERFACE_PERM = 201000302
ERR_INTERFACE_TIMEOUT = 201000303
ERR_INTERFACE_MASTER_TIMEOUT = 201000304
ERR_INTERFACE_SUB_TIMEOUT = 201000305
ERR_INTERFACE_END = 201000399
ERR_BUSINESS_BEGIN = 201001000
ERR_BUSINESS_END = 201009999



_LOGICMSG = _descriptor.Descriptor(
  name='LogicMsg',
  full_name='logic.LogicMsg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='test_req', full_name='logic.LogicMsg.test_req', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='test_rsp', full_name='logic.LogicMsg.test_rsp', index=1,
      number=2, type=11, cpp_type=10, label=1,
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
      name='choice', full_name='logic.LogicMsg.choice',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=36,
  serialized_end=130,
)

_LOGICMSG.fields_by_name['test_req'].message_type = common__pb2._TESTREQ
_LOGICMSG.fields_by_name['test_rsp'].message_type = common__pb2._TESTRSP
_LOGICMSG.oneofs_by_name['choice'].fields.append(
  _LOGICMSG.fields_by_name['test_req'])
_LOGICMSG.fields_by_name['test_req'].containing_oneof = _LOGICMSG.oneofs_by_name['choice']
_LOGICMSG.oneofs_by_name['choice'].fields.append(
  _LOGICMSG.fields_by_name['test_rsp'])
_LOGICMSG.fields_by_name['test_rsp'].containing_oneof = _LOGICMSG.oneofs_by_name['choice']
DESCRIPTOR.message_types_by_name['LogicMsg'] = _LOGICMSG
DESCRIPTOR.enum_types_by_name['ErrorCode'] = _ERRORCODE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

LogicMsg = _reflection.GeneratedProtocolMessageType('LogicMsg', (_message.Message,), dict(
  DESCRIPTOR = _LOGICMSG,
  __module__ = 'logic_pb2'
  # @@protoc_insertion_point(class_scope:logic.LogicMsg)
  ))
_sym_db.RegisterMessage(LogicMsg)


# @@protoc_insertion_point(module_scope)
