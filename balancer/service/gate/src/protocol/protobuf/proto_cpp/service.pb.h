// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: service.proto

#ifndef PROTOBUF_service_2eproto__INCLUDED
#define PROTOBUF_service_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
namespace service {
}  // namespace service

namespace service {

namespace protobuf_service_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_service_2eproto

enum ServiceId {
  BEGIN = 0,
  CLIENT = 100,
  CENTER = 10100,
  NAVIGATE = 10200,
  GATE = 10300,
  SESSION = 10400,
  LOGIN = 10500,
  LOGIC = 10600,
  PROXY = 10700,
  END = 65535,
  ServiceId_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ServiceId_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ServiceId_IsValid(int value);
const ServiceId ServiceId_MIN = BEGIN;
const ServiceId ServiceId_MAX = END;
const int ServiceId_ARRAYSIZE = ServiceId_MAX + 1;

const ::google::protobuf::EnumDescriptor* ServiceId_descriptor();
inline const ::std::string& ServiceId_Name(ServiceId value) {
  return ::google::protobuf::internal::NameOfEnum(
    ServiceId_descriptor(), value);
}
inline bool ServiceId_Parse(
    const ::std::string& name, ServiceId* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ServiceId>(
    ServiceId_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace service

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::service::ServiceId> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::service::ServiceId>() {
  return ::service::ServiceId_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_service_2eproto__INCLUDED
