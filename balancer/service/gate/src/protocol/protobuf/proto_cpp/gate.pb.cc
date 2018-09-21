// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gate.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "gate.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace gate {
class TestReqDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<TestReq>
     _instance;
} _TestReq_default_instance_;
class TestRspDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<TestRsp>
     _instance;
} _TestRsp_default_instance_;
class GateMsgDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<GateMsg>
     _instance;
  const ::gate::TestReq* test_req_;
  const ::gate::TestRsp* test_rsp_;
} _GateMsg_default_instance_;

namespace protobuf_gate_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[3];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestReq, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestReq, service_id_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestRsp, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestRsp, service_name_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GateMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GateMsg, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  offsetof(GateMsgDefaultTypeInternal, test_req_),
  offsetof(GateMsgDefaultTypeInternal, test_rsp_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(GateMsg, choice_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(TestReq)},
  { 6, -1, sizeof(TestRsp)},
  { 12, -1, sizeof(GateMsg)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_TestReq_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&_TestRsp_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&_GateMsg_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "gate.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 3);
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _TestReq_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_TestReq_default_instance_);_TestRsp_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_TestRsp_default_instance_);_GateMsg_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_GateMsg_default_instance_);_GateMsg_default_instance_.test_req_ = const_cast< ::gate::TestReq*>(
      ::gate::TestReq::internal_default_instance());
  _GateMsg_default_instance_.test_rsp_ = const_cast< ::gate::TestRsp*>(
      ::gate::TestRsp::internal_default_instance());
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\ngate.proto\022\004gate\"\035\n\007TestReq\022\022\n\nservice"
      "_id\030\001 \001(\005\"\037\n\007TestRsp\022\024\n\014service_name\030\001 \001"
      "(\014\"Y\n\007GateMsg\022!\n\010test_req\030\001 \001(\0132\r.gate.T"
      "estReqH\000\022!\n\010test_rsp\030\002 \001(\0132\r.gate.TestRs"
      "pH\000B\010\n\006choiceb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 181);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "gate.proto", &protobuf_RegisterTypes);
}
} // anonymous namespace

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_gate_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TestReq::kServiceIdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TestReq::TestReq()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_gate_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:gate.TestReq)
}
TestReq::TestReq(const TestReq& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  service_id_ = from.service_id_;
  // @@protoc_insertion_point(copy_constructor:gate.TestReq)
}

void TestReq::SharedCtor() {
  service_id_ = 0;
  _cached_size_ = 0;
}

TestReq::~TestReq() {
  // @@protoc_insertion_point(destructor:gate.TestReq)
  SharedDtor();
}

void TestReq::SharedDtor() {
}

void TestReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TestReq::descriptor() {
  protobuf_gate_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_gate_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const TestReq& TestReq::default_instance() {
  protobuf_gate_2eproto::InitDefaults();
  return *internal_default_instance();
}

TestReq* TestReq::New(::google::protobuf::Arena* arena) const {
  TestReq* n = new TestReq;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void TestReq::Clear() {
// @@protoc_insertion_point(message_clear_start:gate.TestReq)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  service_id_ = 0;
  _internal_metadata_.Clear();
}

bool TestReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:gate.TestReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 service_id = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &service_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:gate.TestReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:gate.TestReq)
  return false;
#undef DO_
}

void TestReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:gate.TestReq)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 service_id = 1;
  if (this->service_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->service_id(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:gate.TestReq)
}

::google::protobuf::uint8* TestReq::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:gate.TestReq)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 service_id = 1;
  if (this->service_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->service_id(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gate.TestReq)
  return target;
}

size_t TestReq::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:gate.TestReq)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // int32 service_id = 1;
  if (this->service_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->service_id());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TestReq::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:gate.TestReq)
  GOOGLE_DCHECK_NE(&from, this);
  const TestReq* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const TestReq>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:gate.TestReq)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:gate.TestReq)
    MergeFrom(*source);
  }
}

void TestReq::MergeFrom(const TestReq& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:gate.TestReq)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.service_id() != 0) {
    set_service_id(from.service_id());
  }
}

void TestReq::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:gate.TestReq)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TestReq::CopyFrom(const TestReq& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:gate.TestReq)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TestReq::IsInitialized() const {
  return true;
}

void TestReq::Swap(TestReq* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TestReq::InternalSwap(TestReq* other) {
  using std::swap;
  swap(service_id_, other->service_id_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata TestReq::GetMetadata() const {
  protobuf_gate_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_gate_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// TestReq

// int32 service_id = 1;
void TestReq::clear_service_id() {
  service_id_ = 0;
}
::google::protobuf::int32 TestReq::service_id() const {
  // @@protoc_insertion_point(field_get:gate.TestReq.service_id)
  return service_id_;
}
void TestReq::set_service_id(::google::protobuf::int32 value) {
  
  service_id_ = value;
  // @@protoc_insertion_point(field_set:gate.TestReq.service_id)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TestRsp::kServiceNameFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TestRsp::TestRsp()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_gate_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:gate.TestRsp)
}
TestRsp::TestRsp(const TestRsp& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  service_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.service_name().size() > 0) {
    service_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.service_name_);
  }
  // @@protoc_insertion_point(copy_constructor:gate.TestRsp)
}

void TestRsp::SharedCtor() {
  service_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _cached_size_ = 0;
}

TestRsp::~TestRsp() {
  // @@protoc_insertion_point(destructor:gate.TestRsp)
  SharedDtor();
}

void TestRsp::SharedDtor() {
  service_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void TestRsp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TestRsp::descriptor() {
  protobuf_gate_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_gate_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const TestRsp& TestRsp::default_instance() {
  protobuf_gate_2eproto::InitDefaults();
  return *internal_default_instance();
}

TestRsp* TestRsp::New(::google::protobuf::Arena* arena) const {
  TestRsp* n = new TestRsp;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void TestRsp::Clear() {
// @@protoc_insertion_point(message_clear_start:gate.TestRsp)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  service_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

bool TestRsp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:gate.TestRsp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // bytes service_name = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_service_name()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:gate.TestRsp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:gate.TestRsp)
  return false;
#undef DO_
}

void TestRsp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:gate.TestRsp)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes service_name = 1;
  if (this->service_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      1, this->service_name(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:gate.TestRsp)
}

::google::protobuf::uint8* TestRsp::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:gate.TestRsp)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes service_name = 1;
  if (this->service_name().size() > 0) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->service_name(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gate.TestRsp)
  return target;
}

size_t TestRsp::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:gate.TestRsp)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // bytes service_name = 1;
  if (this->service_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->service_name());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TestRsp::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:gate.TestRsp)
  GOOGLE_DCHECK_NE(&from, this);
  const TestRsp* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const TestRsp>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:gate.TestRsp)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:gate.TestRsp)
    MergeFrom(*source);
  }
}

void TestRsp::MergeFrom(const TestRsp& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:gate.TestRsp)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.service_name().size() > 0) {

    service_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.service_name_);
  }
}

void TestRsp::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:gate.TestRsp)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TestRsp::CopyFrom(const TestRsp& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:gate.TestRsp)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TestRsp::IsInitialized() const {
  return true;
}

void TestRsp::Swap(TestRsp* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TestRsp::InternalSwap(TestRsp* other) {
  using std::swap;
  service_name_.Swap(&other->service_name_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata TestRsp::GetMetadata() const {
  protobuf_gate_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_gate_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// TestRsp

// bytes service_name = 1;
void TestRsp::clear_service_name() {
  service_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& TestRsp::service_name() const {
  // @@protoc_insertion_point(field_get:gate.TestRsp.service_name)
  return service_name_.GetNoArena();
}
void TestRsp::set_service_name(const ::std::string& value) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:gate.TestRsp.service_name)
}
#if LANG_CXX11
void TestRsp::set_service_name(::std::string&& value) {
  
  service_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:gate.TestRsp.service_name)
}
#endif
void TestRsp::set_service_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:gate.TestRsp.service_name)
}
void TestRsp::set_service_name(const void* value, size_t size) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:gate.TestRsp.service_name)
}
::std::string* TestRsp::mutable_service_name() {
  
  // @@protoc_insertion_point(field_mutable:gate.TestRsp.service_name)
  return service_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* TestRsp::release_service_name() {
  // @@protoc_insertion_point(field_release:gate.TestRsp.service_name)
  
  return service_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void TestRsp::set_allocated_service_name(::std::string* service_name) {
  if (service_name != NULL) {
    
  } else {
    
  }
  service_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), service_name);
  // @@protoc_insertion_point(field_set_allocated:gate.TestRsp.service_name)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int GateMsg::kTestReqFieldNumber;
const int GateMsg::kTestRspFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

GateMsg::GateMsg()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_gate_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:gate.GateMsg)
}
GateMsg::GateMsg(const GateMsg& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  clear_has_choice();
  switch (from.choice_case()) {
    case kTestReq: {
      mutable_test_req()->::gate::TestReq::MergeFrom(from.test_req());
      break;
    }
    case kTestRsp: {
      mutable_test_rsp()->::gate::TestRsp::MergeFrom(from.test_rsp());
      break;
    }
    case CHOICE_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:gate.GateMsg)
}

void GateMsg::SharedCtor() {
  clear_has_choice();
  _cached_size_ = 0;
}

GateMsg::~GateMsg() {
  // @@protoc_insertion_point(destructor:gate.GateMsg)
  SharedDtor();
}

void GateMsg::SharedDtor() {
  if (has_choice()) {
    clear_choice();
  }
}

void GateMsg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* GateMsg::descriptor() {
  protobuf_gate_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_gate_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const GateMsg& GateMsg::default_instance() {
  protobuf_gate_2eproto::InitDefaults();
  return *internal_default_instance();
}

GateMsg* GateMsg::New(::google::protobuf::Arena* arena) const {
  GateMsg* n = new GateMsg;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void GateMsg::clear_choice() {
// @@protoc_insertion_point(one_of_clear_start:gate.GateMsg)
  switch (choice_case()) {
    case kTestReq: {
      delete choice_.test_req_;
      break;
    }
    case kTestRsp: {
      delete choice_.test_rsp_;
      break;
    }
    case CHOICE_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = CHOICE_NOT_SET;
}


void GateMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:gate.GateMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  clear_choice();
  _internal_metadata_.Clear();
}

bool GateMsg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:gate.GateMsg)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .gate.TestReq test_req = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_test_req()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .gate.TestRsp test_rsp = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_test_rsp()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:gate.GateMsg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:gate.GateMsg)
  return false;
#undef DO_
}

void GateMsg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:gate.GateMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .gate.TestReq test_req = 1;
  if (has_test_req()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *choice_.test_req_, output);
  }

  // .gate.TestRsp test_rsp = 2;
  if (has_test_rsp()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, *choice_.test_rsp_, output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:gate.GateMsg)
}

::google::protobuf::uint8* GateMsg::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:gate.GateMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .gate.TestReq test_req = 1;
  if (has_test_req()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, *choice_.test_req_, deterministic, target);
  }

  // .gate.TestRsp test_rsp = 2;
  if (has_test_rsp()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        2, *choice_.test_rsp_, deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:gate.GateMsg)
  return target;
}

size_t GateMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:gate.GateMsg)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  switch (choice_case()) {
    // .gate.TestReq test_req = 1;
    case kTestReq: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *choice_.test_req_);
      break;
    }
    // .gate.TestRsp test_rsp = 2;
    case kTestRsp: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *choice_.test_rsp_);
      break;
    }
    case CHOICE_NOT_SET: {
      break;
    }
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void GateMsg::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:gate.GateMsg)
  GOOGLE_DCHECK_NE(&from, this);
  const GateMsg* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const GateMsg>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:gate.GateMsg)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:gate.GateMsg)
    MergeFrom(*source);
  }
}

void GateMsg::MergeFrom(const GateMsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:gate.GateMsg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  switch (from.choice_case()) {
    case kTestReq: {
      mutable_test_req()->::gate::TestReq::MergeFrom(from.test_req());
      break;
    }
    case kTestRsp: {
      mutable_test_rsp()->::gate::TestRsp::MergeFrom(from.test_rsp());
      break;
    }
    case CHOICE_NOT_SET: {
      break;
    }
  }
}

void GateMsg::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:gate.GateMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GateMsg::CopyFrom(const GateMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:gate.GateMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GateMsg::IsInitialized() const {
  return true;
}

void GateMsg::Swap(GateMsg* other) {
  if (other == this) return;
  InternalSwap(other);
}
void GateMsg::InternalSwap(GateMsg* other) {
  using std::swap;
  swap(choice_, other->choice_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata GateMsg::GetMetadata() const {
  protobuf_gate_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_gate_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// GateMsg

// .gate.TestReq test_req = 1;
bool GateMsg::has_test_req() const {
  return choice_case() == kTestReq;
}
void GateMsg::set_has_test_req() {
  _oneof_case_[0] = kTestReq;
}
void GateMsg::clear_test_req() {
  if (has_test_req()) {
    delete choice_.test_req_;
    clear_has_choice();
  }
}
 const ::gate::TestReq& GateMsg::test_req() const {
  // @@protoc_insertion_point(field_get:gate.GateMsg.test_req)
  return has_test_req()
      ? *choice_.test_req_
      : ::gate::TestReq::default_instance();
}
::gate::TestReq* GateMsg::mutable_test_req() {
  if (!has_test_req()) {
    clear_choice();
    set_has_test_req();
    choice_.test_req_ = new ::gate::TestReq;
  }
  // @@protoc_insertion_point(field_mutable:gate.GateMsg.test_req)
  return choice_.test_req_;
}
::gate::TestReq* GateMsg::release_test_req() {
  // @@protoc_insertion_point(field_release:gate.GateMsg.test_req)
  if (has_test_req()) {
    clear_has_choice();
    ::gate::TestReq* temp = choice_.test_req_;
    choice_.test_req_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void GateMsg::set_allocated_test_req(::gate::TestReq* test_req) {
  clear_choice();
  if (test_req) {
    set_has_test_req();
    choice_.test_req_ = test_req;
  }
  // @@protoc_insertion_point(field_set_allocated:gate.GateMsg.test_req)
}

// .gate.TestRsp test_rsp = 2;
bool GateMsg::has_test_rsp() const {
  return choice_case() == kTestRsp;
}
void GateMsg::set_has_test_rsp() {
  _oneof_case_[0] = kTestRsp;
}
void GateMsg::clear_test_rsp() {
  if (has_test_rsp()) {
    delete choice_.test_rsp_;
    clear_has_choice();
  }
}
 const ::gate::TestRsp& GateMsg::test_rsp() const {
  // @@protoc_insertion_point(field_get:gate.GateMsg.test_rsp)
  return has_test_rsp()
      ? *choice_.test_rsp_
      : ::gate::TestRsp::default_instance();
}
::gate::TestRsp* GateMsg::mutable_test_rsp() {
  if (!has_test_rsp()) {
    clear_choice();
    set_has_test_rsp();
    choice_.test_rsp_ = new ::gate::TestRsp;
  }
  // @@protoc_insertion_point(field_mutable:gate.GateMsg.test_rsp)
  return choice_.test_rsp_;
}
::gate::TestRsp* GateMsg::release_test_rsp() {
  // @@protoc_insertion_point(field_release:gate.GateMsg.test_rsp)
  if (has_test_rsp()) {
    clear_has_choice();
    ::gate::TestRsp* temp = choice_.test_rsp_;
    choice_.test_rsp_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void GateMsg::set_allocated_test_rsp(::gate::TestRsp* test_rsp) {
  clear_choice();
  if (test_rsp) {
    set_has_test_rsp();
    choice_.test_rsp_ = test_rsp;
  }
  // @@protoc_insertion_point(field_set_allocated:gate.GateMsg.test_rsp)
}

bool GateMsg::has_choice() const {
  return choice_case() != CHOICE_NOT_SET;
}
void GateMsg::clear_has_choice() {
  _oneof_case_[0] = CHOICE_NOT_SET;
}
GateMsg::ChoiceCase GateMsg::choice_case() const {
  return GateMsg::ChoiceCase(_oneof_case_[0]);
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace gate

// @@protoc_insertion_point(global_scope)
