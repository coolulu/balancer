// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: proxy.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "proxy.pb.h"

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

namespace proxy {
class ProxyMsgDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<ProxyMsg>
     _instance;
  const ::common::TestReq* test_req_;
  const ::common::TestRsp* test_rsp_;
} _ProxyMsg_default_instance_;

namespace protobuf_proxy_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

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
};

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProxyMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProxyMsg, _oneof_case_[0]),
  ~0u,  // no _weak_field_map_
  offsetof(ProxyMsgDefaultTypeInternal, test_req_),
  offsetof(ProxyMsgDefaultTypeInternal, test_rsp_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ProxyMsg, choice_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(ProxyMsg)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_ProxyMsg_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "proxy.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  ::common::protobuf_common_2eproto::InitDefaults();
  _ProxyMsg_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_ProxyMsg_default_instance_);_ProxyMsg_default_instance_.test_req_ = const_cast< ::common::TestReq*>(
      ::common::TestReq::internal_default_instance());
  _ProxyMsg_default_instance_.test_rsp_ = const_cast< ::common::TestRsp*>(
      ::common::TestRsp::internal_default_instance());
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\013proxy.proto\022\005proxy\032\014common.proto\"^\n\010Pr"
      "oxyMsg\022#\n\010test_req\030\001 \001(\0132\017.common.TestRe"
      "qH\000\022#\n\010test_rsp\030\002 \001(\0132\017.common.TestRspH\000"
      "B\010\n\006choice*\376\010\n\tErrorCode\022\013\n\007SUCCESS\020\000\022\025\n"
      "\rERR_SYS_BEGIN\020\244\313\303\217\001\022\030\n\020ERR_SYS_OVERLOAD"
      "\020\245\313\303\217\001\022\036\n\026ERR_SYS_REJECT_SERVICE\020\246\313\303\217\001\022\034"
      "\n\024ERR_SYS_SERVER_INNER\020\247\313\303\217\001\022\027\n\017ERR_SYS_"
      "TIMEOUT\020\250\313\303\217\001\022!\n\031ERR_SYS_NO_INSERVICE_LI"
      "ST\020\251\313\303\217\001\022\032\n\022ERR_SYS_TASK_STATE\020\252\313\303\217\001\022\034\n\024"
      "ERR_SYS_TASK_DISCARD\020\253\313\303\217\001\022\023\n\013ERR_SYS_EN"
      "D\020\207\314\303\217\001\022\030\n\020ERR_PACKET_BEGIN\020\210\314\303\217\001\022\031\n\021ERR"
      "_PACKET_ENCODE\020\211\314\303\217\001\022\031\n\021ERR_PACKET_DECOD"
      "E\020\212\314\303\217\001\022\031\n\021ERR_PACKET_HEADER\020\213\314\303\217\001\022\026\n\016ER"
      "R_PACKET_LEN\020\214\314\303\217\001\022\032\n\022ERR_PACKET_VERSION"
      "\020\215\314\303\217\001\022\"\n\032ERR_PACKET_FROM_SERVICE_ID\020\216\314\303"
      "\217\001\022 \n\030ERR_PACKET_TO_SERVICE_ID\020\217\314\303\217\001\022\031\n\021"
      "ERR_PACKET_APP_ID\020\220\314\303\217\001\022\036\n\026ERR_PACKET_AP"
      "P_VERSION\020\221\314\303\217\001\022\036\n\026ERR_PACKET_CONN_SEQ_I"
      "D\020\222\314\303\217\001\022\035\n\025ERR_PACKET_MSG_SEQ_ID\020\223\314\303\217\001\022\036"
      "\n\026ERR_PACKET_DATA_FORMAT\020\224\314\303\217\001\022\037\n\027ERR_PA"
      "CKET_DATA_FIELD_0\020\225\314\303\217\001\022\037\n\027ERR_PACKET_DA"
      "TA_FIELD_1\020\226\314\303\217\001\022\037\n\027ERR_PACKET_DATA_FIEL"
      "D_2\020\227\314\303\217\001\022\037\n\027ERR_PACKET_DATA_FIELD_3\020\230\314\303"
      "\217\001\022\034\n\024ERR_PACKET_CHECK_SUM\020\231\314\303\217\001\022\"\n\032ERR_"
      "PACKET_UNKNOWN_REQUEST\020\232\314\303\217\001\022\026\n\016ERR_PACK"
      "ET_END\020\353\314\303\217\001\022\033\n\023ERR_INTERFACE_BEGIN\020\354\314\303\217"
      "\001\022\033\n\023ERR_INTERFACE_PARAM\020\355\314\303\217\001\022\032\n\022ERR_IN"
      "TERFACE_PERM\020\356\314\303\217\001\022\035\n\025ERR_INTERFACE_TIME"
      "OUT\020\357\314\303\217\001\022$\n\034ERR_INTERFACE_MASTER_TIMEOU"
      "T\020\360\314\303\217\001\022!\n\031ERR_INTERFACE_SUB_TIMEOUT\020\361\314\303"
      "\217\001\022\031\n\021ERR_INTERFACE_END\020\317\315\303\217\001\022\032\n\022ERR_BUS"
      "INESS_BEGIN\020\250\322\303\217\001\022\030\n\020ERR_BUSINESS_END\020\317\230"
      "\304\217\001b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 1291);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "proxy.proto", &protobuf_RegisterTypes);
  ::common::protobuf_common_2eproto::AddDescriptors();
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

}  // namespace protobuf_proxy_2eproto

const ::google::protobuf::EnumDescriptor* ErrorCode_descriptor() {
  protobuf_proxy_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_proxy_2eproto::file_level_enum_descriptors[0];
}
bool ErrorCode_IsValid(int value) {
  switch (value) {
    case 0:
    case 301000100:
    case 301000101:
    case 301000102:
    case 301000103:
    case 301000104:
    case 301000105:
    case 301000106:
    case 301000107:
    case 301000199:
    case 301000200:
    case 301000201:
    case 301000202:
    case 301000203:
    case 301000204:
    case 301000205:
    case 301000206:
    case 301000207:
    case 301000208:
    case 301000209:
    case 301000210:
    case 301000211:
    case 301000212:
    case 301000213:
    case 301000214:
    case 301000215:
    case 301000216:
    case 301000217:
    case 301000218:
    case 301000299:
    case 301000300:
    case 301000301:
    case 301000302:
    case 301000303:
    case 301000304:
    case 301000305:
    case 301000399:
    case 301001000:
    case 301009999:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ProxyMsg::kTestReqFieldNumber;
const int ProxyMsg::kTestRspFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ProxyMsg::ProxyMsg()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_proxy_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:proxy.ProxyMsg)
}
ProxyMsg::ProxyMsg(const ProxyMsg& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  clear_has_choice();
  switch (from.choice_case()) {
    case kTestReq: {
      mutable_test_req()->::common::TestReq::MergeFrom(from.test_req());
      break;
    }
    case kTestRsp: {
      mutable_test_rsp()->::common::TestRsp::MergeFrom(from.test_rsp());
      break;
    }
    case CHOICE_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:proxy.ProxyMsg)
}

void ProxyMsg::SharedCtor() {
  clear_has_choice();
  _cached_size_ = 0;
}

ProxyMsg::~ProxyMsg() {
  // @@protoc_insertion_point(destructor:proxy.ProxyMsg)
  SharedDtor();
}

void ProxyMsg::SharedDtor() {
  if (has_choice()) {
    clear_choice();
  }
}

void ProxyMsg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ProxyMsg::descriptor() {
  protobuf_proxy_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_proxy_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ProxyMsg& ProxyMsg::default_instance() {
  protobuf_proxy_2eproto::InitDefaults();
  return *internal_default_instance();
}

ProxyMsg* ProxyMsg::New(::google::protobuf::Arena* arena) const {
  ProxyMsg* n = new ProxyMsg;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ProxyMsg::clear_choice() {
// @@protoc_insertion_point(one_of_clear_start:proxy.ProxyMsg)
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


void ProxyMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:proxy.ProxyMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  clear_choice();
  _internal_metadata_.Clear();
}

bool ProxyMsg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:proxy.ProxyMsg)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .common.TestReq test_req = 1;
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

      // .common.TestRsp test_rsp = 2;
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
  // @@protoc_insertion_point(parse_success:proxy.ProxyMsg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:proxy.ProxyMsg)
  return false;
#undef DO_
}

void ProxyMsg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:proxy.ProxyMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .common.TestReq test_req = 1;
  if (has_test_req()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *choice_.test_req_, output);
  }

  // .common.TestRsp test_rsp = 2;
  if (has_test_rsp()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, *choice_.test_rsp_, output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:proxy.ProxyMsg)
}

::google::protobuf::uint8* ProxyMsg::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:proxy.ProxyMsg)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .common.TestReq test_req = 1;
  if (has_test_req()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, *choice_.test_req_, deterministic, target);
  }

  // .common.TestRsp test_rsp = 2;
  if (has_test_rsp()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        2, *choice_.test_rsp_, deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:proxy.ProxyMsg)
  return target;
}

size_t ProxyMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:proxy.ProxyMsg)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  switch (choice_case()) {
    // .common.TestReq test_req = 1;
    case kTestReq: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *choice_.test_req_);
      break;
    }
    // .common.TestRsp test_rsp = 2;
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

void ProxyMsg::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:proxy.ProxyMsg)
  GOOGLE_DCHECK_NE(&from, this);
  const ProxyMsg* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ProxyMsg>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:proxy.ProxyMsg)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:proxy.ProxyMsg)
    MergeFrom(*source);
  }
}

void ProxyMsg::MergeFrom(const ProxyMsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:proxy.ProxyMsg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  switch (from.choice_case()) {
    case kTestReq: {
      mutable_test_req()->::common::TestReq::MergeFrom(from.test_req());
      break;
    }
    case kTestRsp: {
      mutable_test_rsp()->::common::TestRsp::MergeFrom(from.test_rsp());
      break;
    }
    case CHOICE_NOT_SET: {
      break;
    }
  }
}

void ProxyMsg::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:proxy.ProxyMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ProxyMsg::CopyFrom(const ProxyMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:proxy.ProxyMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ProxyMsg::IsInitialized() const {
  return true;
}

void ProxyMsg::Swap(ProxyMsg* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ProxyMsg::InternalSwap(ProxyMsg* other) {
  using std::swap;
  swap(choice_, other->choice_);
  swap(_oneof_case_[0], other->_oneof_case_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ProxyMsg::GetMetadata() const {
  protobuf_proxy_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_proxy_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ProxyMsg

// .common.TestReq test_req = 1;
bool ProxyMsg::has_test_req() const {
  return choice_case() == kTestReq;
}
void ProxyMsg::set_has_test_req() {
  _oneof_case_[0] = kTestReq;
}
void ProxyMsg::clear_test_req() {
  if (has_test_req()) {
    delete choice_.test_req_;
    clear_has_choice();
  }
}
 const ::common::TestReq& ProxyMsg::test_req() const {
  // @@protoc_insertion_point(field_get:proxy.ProxyMsg.test_req)
  return has_test_req()
      ? *choice_.test_req_
      : ::common::TestReq::default_instance();
}
::common::TestReq* ProxyMsg::mutable_test_req() {
  if (!has_test_req()) {
    clear_choice();
    set_has_test_req();
    choice_.test_req_ = new ::common::TestReq;
  }
  // @@protoc_insertion_point(field_mutable:proxy.ProxyMsg.test_req)
  return choice_.test_req_;
}
::common::TestReq* ProxyMsg::release_test_req() {
  // @@protoc_insertion_point(field_release:proxy.ProxyMsg.test_req)
  if (has_test_req()) {
    clear_has_choice();
    ::common::TestReq* temp = choice_.test_req_;
    choice_.test_req_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void ProxyMsg::set_allocated_test_req(::common::TestReq* test_req) {
  clear_choice();
  if (test_req) {
    set_has_test_req();
    choice_.test_req_ = test_req;
  }
  // @@protoc_insertion_point(field_set_allocated:proxy.ProxyMsg.test_req)
}

// .common.TestRsp test_rsp = 2;
bool ProxyMsg::has_test_rsp() const {
  return choice_case() == kTestRsp;
}
void ProxyMsg::set_has_test_rsp() {
  _oneof_case_[0] = kTestRsp;
}
void ProxyMsg::clear_test_rsp() {
  if (has_test_rsp()) {
    delete choice_.test_rsp_;
    clear_has_choice();
  }
}
 const ::common::TestRsp& ProxyMsg::test_rsp() const {
  // @@protoc_insertion_point(field_get:proxy.ProxyMsg.test_rsp)
  return has_test_rsp()
      ? *choice_.test_rsp_
      : ::common::TestRsp::default_instance();
}
::common::TestRsp* ProxyMsg::mutable_test_rsp() {
  if (!has_test_rsp()) {
    clear_choice();
    set_has_test_rsp();
    choice_.test_rsp_ = new ::common::TestRsp;
  }
  // @@protoc_insertion_point(field_mutable:proxy.ProxyMsg.test_rsp)
  return choice_.test_rsp_;
}
::common::TestRsp* ProxyMsg::release_test_rsp() {
  // @@protoc_insertion_point(field_release:proxy.ProxyMsg.test_rsp)
  if (has_test_rsp()) {
    clear_has_choice();
    ::common::TestRsp* temp = choice_.test_rsp_;
    choice_.test_rsp_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void ProxyMsg::set_allocated_test_rsp(::common::TestRsp* test_rsp) {
  clear_choice();
  if (test_rsp) {
    set_has_test_rsp();
    choice_.test_rsp_ = test_rsp;
  }
  // @@protoc_insertion_point(field_set_allocated:proxy.ProxyMsg.test_rsp)
}

bool ProxyMsg::has_choice() const {
  return choice_case() != CHOICE_NOT_SET;
}
void ProxyMsg::clear_has_choice() {
  _oneof_case_[0] = CHOICE_NOT_SET;
}
ProxyMsg::ChoiceCase ProxyMsg::choice_case() const {
  return ProxyMsg::ChoiceCase(_oneof_case_[0]);
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace proxy

// @@protoc_insertion_point(global_scope)
