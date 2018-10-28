#pragma once

#include "proto_cpp/data.pb.h"
#include "proto_cpp/gate.pb.h"
#include "core/Packet.h"

namespace GateStack
{
	void CloseConnIdReq(data::Body& body, unsigned long long conn_id);

	void SetConnLoginReq(data::Body& body, unsigned long long conn_id);
}