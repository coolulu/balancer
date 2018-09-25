#include "HandleClient.h"

#include "core/Proc.h"
#include "protocol/Protocol.h"

HandleClient::HandleClient(Proc& proc)
	: _proc(proc)
{

}

HandleClient::~HandleClient()
{

}

void HandleClient::forward_response_to_client(const muduo::net::TcpConnectionPtr& conn, 
											  PacketPtr& packet_ptr,
											  muduo::Timestamp time)
{

}
