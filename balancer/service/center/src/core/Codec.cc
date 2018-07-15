#include "Codec.h"

#include <zlib.h>
#include <muduo/net/Endian.h>
#include "log/Log.h"
 
Codec::Codec(const PacketMessageCallback& cb, 
			 const std::string& name, 
			 unsigned int& tcp_recv_packet_len_max, 
			 unsigned int& tcp_send_packet_len_max)
	:	_messageCallback(cb),
		_name(name),
		_tcp_recv_packet_len_max(tcp_recv_packet_len_max), 
		_tcp_send_packet_len_max(tcp_send_packet_len_max)
{

}

void Codec::on_stream_message(const muduo::net::TcpConnectionPtr& conn,
							  muduo::net::Buffer* buf,
							  muduo::Timestamp receiveTime)
{
	size_t readableBytes = 0;
	while ((readableBytes = buf->readableBytes()) > Packet::k_header_size + Packet::k_len_size)
	{
		B_LOG_INFO << "_name=" << _name << ", readableBytes=" << readableBytes;

		const void* header_data = buf->peek();
		uint32_t header_be = *static_cast<const uint32_t*>(header_data);
		const uint32_t header = muduo::net::sockets::networkToHost32(header_be);

		B_LOG_INFO << "_name=" << _name << ", recv header=" << header << ", header_be=" << header_be;

		if(header != Packet::k_header)
		{
			B_LOG_ERROR << "_name=" << _name << ", shutdown conn, header=" << header << "is not k_header=" << Packet::k_header;
			conn->shutdown(); // FIXME: disable reading
			break;
		}

		const void* len_data = buf->peek() + Packet::k_header_size;
		uint32_t len_be = *static_cast<const uint32_t*>(len_data); // SIGBUS
		const uint32_t len = muduo::net::sockets::networkToHost32(len_be);

		B_LOG_INFO << "_name=" << _name << ", recv len=" << len << ", len_be=" << len_be;

		if (len > _tcp_recv_packet_len_max)
		{
			B_LOG_ERROR << "_name=" << _name << ", shutdown conn, len=" << len << " more than _tcp_recv_packet_len_max=" << _tcp_recv_packet_len_max;
			conn->shutdown();  // FIXME: disable reading
			break;
		}
		else if (len == 0)
		{
			B_LOG_ERROR << "_name=" << _name << ", shutdown conn, len=0";
			conn->shutdown();  // FIXME: disable reading
			break;
		}

		readableBytes = buf->readableBytes();
		if (readableBytes >= Packet::k_len_size + len)
		{
			PacketPtr packet_ptr(new Packet(header, buf->peek(), len));
			packet_ptr->print();
			bool b = packet_ptr->check();
			if(b)
			{
				_messageCallback(conn, packet_ptr, receiveTime);
				buf->retrieve(Packet::k_header_size + Packet::k_len_size + len);
			}
			else
			{
				B_LOG_ERROR << "_name=" << _name << ", shutdown conn, packet.check=false";
				conn->shutdown();  // FIXME: disable reading
				break;
			}
		}
		else
		{
			break;
		}
	}
}

void Codec::send_stream(muduo::net::TcpConnection* conn, 
						PacketPtr& packet_ptr)
{
	unsigned short      version_be			= muduo::net::sockets::hostToNetwork16(packet_ptr->_version);	
	unsigned short      from_service_id_be	= muduo::net::sockets::hostToNetwork16(packet_ptr->_from_service_id);
	unsigned short      to_service_id_be	= muduo::net::sockets::hostToNetwork16(packet_ptr->_to_service_id);
	unsigned int		to_proc_id_be		= muduo::net::sockets::hostToNetwork32(packet_ptr->_to_proc_id);
	unsigned int        app_id_be 			= muduo::net::sockets::hostToNetwork32(packet_ptr->_app_id);
	unsigned int		app_version_be		= muduo::net::sockets::hostToNetwork32(packet_ptr->_app_version);
	unsigned long long	conn_seq_id_be 		= muduo::net::sockets::hostToNetwork64(packet_ptr->_conn_seq_id);
	unsigned long long  msg_seq_id_be		= muduo::net::sockets::hostToNetwork64(packet_ptr->_msg_seq_id);
	unsigned char		data_format_be		= packet_ptr->_data_format;
	unsigned int		data_len			= packet_ptr->_body.ByteSize();
	unsigned char*		data				= new unsigned char[data_len];
	unsigned char		reserve_field_0_be	= packet_ptr->_reserve_field_0;
	unsigned int        reserve_field_1_be	= muduo::net::sockets::hostToNetwork32(packet_ptr->_reserve_field_1);
	unsigned int        reserve_field_2_be	= muduo::net::sockets::hostToNetwork32(packet_ptr->_reserve_field_2);
	unsigned int        reserve_field_3_be	= muduo::net::sockets::hostToNetwork32(packet_ptr->_reserve_field_3);

	bool b = packet_ptr->_body.SerializeToArray(data, data_len);
	if(b)
	{
		muduo::net::Buffer buf;
		uint32_t len = Packet::s_data_offset + data_len + Packet::k_check_sum_size - Packet::s_version_offset;
		uint32_t len_be = muduo::net::sockets::hostToNetwork32(len);
		buf.prepend(&len_be, sizeof len_be);

		buf.append(&version_be, sizeof version_be);
		buf.append(&from_service_id_be, sizeof from_service_id_be);
		buf.append(&to_service_id_be, sizeof to_service_id_be);
		buf.append(&to_proc_id_be, sizeof to_proc_id_be);
		buf.append(&app_id_be, sizeof app_id_be);
		buf.append(&app_version_be, sizeof app_version_be);
		buf.append(&conn_seq_id_be, sizeof conn_seq_id_be);
		buf.append(&msg_seq_id_be, sizeof msg_seq_id_be);
		buf.append(&data_format_be, sizeof data_format_be);
		buf.append(&reserve_field_0_be, sizeof reserve_field_0_be);
		buf.append(&reserve_field_1_be, sizeof reserve_field_1_be);
		buf.append(&reserve_field_2_be, sizeof reserve_field_2_be);
		buf.append(&reserve_field_3_be, sizeof reserve_field_3_be);
		buf.append(data, data_len);

		unsigned int check_sum = ::adler32(0, reinterpret_cast<const Bytef*>(buf.peek()),
			buf.readableBytes());
		unsigned int check_sum_be = muduo::net::sockets::hostToNetwork32(check_sum);
		buf.append(&check_sum_be, sizeof check_sum_be);

		uint32_t header_be = muduo::net::sockets::hostToNetwork32(Packet::k_header);
		buf.prepend(&header_be, sizeof header_be);

		B_LOG_INFO << "_name=" << _name << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", send k_header=" << Packet::k_header << ", header_be=" << header_be << ", len=" << len << ", len_be=" << len_be;
		if(len > _tcp_send_packet_len_max)
		{
			B_LOG_WARN << "_name=" << _name << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << ", len=" << len << " more than _tcp_send_packet_len_max=" << _tcp_send_packet_len_max;
		}

		conn->send(&buf);
	}
	else
	{
		B_LOG_ERROR << "_name=" << _name << ", _msg_seq_id=" << packet_ptr->_msg_seq_id << " SerializeToArray=false";
	}

	delete [] data;
	data = nullptr;
}
