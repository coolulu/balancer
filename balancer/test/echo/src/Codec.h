#pragma once

#include <muduo/base/Logging.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/Endian.h>
#include <muduo/net/TcpConnection.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

//修改muduo/examples/asio/chat/codec.h
class Codec : boost::noncopyable
{
 public:
  typedef boost::function<void (const muduo::net::TcpConnectionPtr&,
                                const muduo::string& message,
                                muduo::Timestamp)> StringMessageCallback;

  explicit Codec(const StringMessageCallback& cb)
    : messageCallback_(cb)
  {
  }

  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp receiveTime)
  {
	//muduo自带脱去包头[0x00, 0x00, 0x00, 0x00]
	size_t readableBytes = 0;
    while ((readableBytes = buf->readableBytes()) > kHeaderLen)
    {
      // FIXME: use Buffer::peekInt32()
      const void* data = buf->peek();
      uint32_t be32 = *static_cast<const uint32_t*>(data); // SIGBUS
      const uint32_t len = muduo::net::sockets::networkToHost32(be32);

	  LOG_INFO << "recv len: " << len;
	  LOG_INFO << "recv be32 " << be32;

      if (len > (unsigned short)-1)
      {
        LOG_ERROR << "Invalid length " << len;
        conn->shutdown();  // FIXME: disable reading
        break;
      }
      
	  readableBytes = buf->readableBytes();
	  if (readableBytes >= kHeaderLen + len)
      {
        buf->retrieve(kHeaderLen);
        muduo::string message(buf->peek(), len);
        messageCallback_(conn, message, receiveTime);
        buf->retrieve(len);
      }
      else
      {
        break;
      }
    }
  }

  // FIXME: TcpConnectionPtr
  void send(muduo::net::TcpConnection* conn,
            const muduo::StringPiece& message)
  {
    muduo::net::Buffer buf;
    buf.append(message.data(), message.size());
    uint32_t len = static_cast<int32_t>(message.size());
    uint32_t be32 = muduo::net::sockets::hostToNetwork32(len);
    buf.prepend(&be32, sizeof be32);

	LOG_INFO << "send len: " << len;
	LOG_INFO << "send be32 " << be32;

    conn->send(&buf); //muduo自带加包头[0x00, 0x00, 0x00, 0x00]
  }

 private:
  StringMessageCallback messageCallback_;
  const static size_t kHeaderLen = sizeof(uint32_t);
};


