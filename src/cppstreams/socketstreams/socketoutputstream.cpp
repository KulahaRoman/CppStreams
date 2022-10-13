#include "socketoutputstream.h"

SocketOutputStream::SocketOutputStream(boost::asio::ip::tcp::socket&& socket)
    : AbstractSocketStream(std::move(socket)) {}

uint64_t SocketOutputStream::Write(const unsigned char* data, uint64_t size) {
  return write(data, size);
}

void SocketOutputStream::Write(
    const unsigned char* data, uint64_t size,
    const std::function<void(uint64_t)>& onSuccess,
    const std::function<void(const Exception&)>& onFailure) {
  write(data, size, onSuccess, onFailure);
}

uint64_t SocketOutputStream::Flush() { return flush(); }

void SocketOutputStream::Flush(
    const std::function<void(uint64_t)>& onSuccess,
    const std::function<void(const Exception&)>& onFailure) {
  flush(onSuccess, onFailure);
}