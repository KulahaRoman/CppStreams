#pragma once
#include "../outputstream.h"
#include "abstracts/abstractsocketoutputstream.h"

class SocketOutputStream : private AbstractSocketOutputStream,
                           public OutputStream {
 public:
  SocketOutputStream(boost::asio::ip::tcp::socket&& socket);

  uint64_t Write(const unsigned char* data, uint64_t size) override;
  void Write(const unsigned char* data, uint64_t size,
             const std::function<void(uint64_t)>& onSuccess,
             const std::function<void(const Exception&)>& onFailure =
                 nullptr) override;

  uint64_t Flush() override;
  void Flush(const std::function<void(uint64_t)>& onSuccess,
             const std::function<void(const Exception&)>& onFailure =
                 nullptr) override;
};
