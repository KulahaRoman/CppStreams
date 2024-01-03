#include "abstractsocketinputstream.h"

namespace CppStreams {
uint64_t AbstractSocketInputStream::Read(unsigned char* data, uint64_t size) {
  if (!size) {
    return size;
  }

  uint64_t bytesRead = 0ull;

  auto tempBuffer =
      std::make_shared<std::vector<unsigned char>>(static_cast<size_t>(size));

  try {
    bytesRead = boost::asio::read(
        socket, boost::asio::buffer(tempBuffer->data(), tempBuffer->size()));
  } catch (...) {
    throw std::runtime_error("Failed to read bytes (IO error).");
  }

  std::copy(tempBuffer->data(), tempBuffer->data() + tempBuffer->size(), data);

  return bytesRead;
}

void AbstractSocketInputStream::Read(
    unsigned char* data, uint64_t size,
    const std::function<void(uint64_t)>& onSuccess,
    const std::function<void(const std::exception&)>& onFailure) {
  if (!size) {
    if (onSuccess) {
      onSuccess(size);
    }
    return;
  }

  auto tempBuffer =
      std::make_shared<std::vector<unsigned char>>(static_cast<size_t>(size));

  boost::asio::async_read(
      socket, boost::asio::buffer(tempBuffer->data(), tempBuffer->size()),
      [this, tempBuffer, data, onSuccess, onFailure, self = shared_from_this()](
          const auto& error, const auto& bytesRead) {
        if (error) {
          if (onFailure) {
            onFailure(std::runtime_error("Failed to read bytes (IO error)."));
          }
          return;
        }

        std::copy(tempBuffer->data(), tempBuffer->data() + tempBuffer->size(),
                  data);

        if (onSuccess) {
          onSuccess(bytesRead);
        }
      });
}

uint64_t AbstractSocketInputStream::Skip(uint64_t nBytes) {
  if (!nBytes) {
    return nBytes;
  }

  uint64_t bytesSkipped = 0ull;

  std::vector<unsigned char> tempBuffer(static_cast<size_t>(nBytes));

  try {
    bytesSkipped = boost::asio::read(
        socket, boost::asio::buffer(tempBuffer.data(), tempBuffer.size()));
  } catch (...) {
    throw std::runtime_error("Failed to skip bytes (IO error).");
  }

  return bytesSkipped;
}

void AbstractSocketInputStream::Skip(
    uint64_t nBytes, const std::function<void(uint64_t)>& onSuccess,
    const std::function<void(const std::exception&)>& onFailure) {
  if (!nBytes) {
    if (onSuccess) {
      onSuccess(nBytes);
    }
    return;
  }

  auto tempBuffer =
      std::make_shared<std::vector<unsigned char>>(static_cast<size_t>(nBytes));

  boost::asio::async_read(
      socket, boost::asio::buffer(tempBuffer->data(), tempBuffer->size()),
      [this, onSuccess, onFailure, self = shared_from_this()](
          const auto& error, const auto& bytesRead) {
        if (error) {
          if (onFailure) {
            onFailure(std::runtime_error("Failed to skip bytes (IO error)."));
          }
          return;
        }

        if (onSuccess) {
          onSuccess(bytesRead);
        }
      });
}

uint64_t AbstractSocketInputStream::Available() {
  return static_cast<uint64_t>(socket.available());
}
}  // namespace CppStreams
