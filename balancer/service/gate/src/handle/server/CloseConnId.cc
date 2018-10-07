#include "CloseConnId.h"

CloseConnId::CloseConnId(Proc& proc, 
						 const muduo::net::TcpConnectionPtr& conn, 
						 PacketPtr& packet_ptr, 
						 muduo::Timestamp time)
	:	_proc(proc)
{

}

CloseConnId::~CloseConnId()
{

}

void CloseConnId::handle(const gate::GateMsg& msg)
{

}
