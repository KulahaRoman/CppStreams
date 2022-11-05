#include "bufferedoutputstream.h"

BufferedOutputStream::BufferedOutputStream(OutputStream& stream,
                                           uint64_t bufferSize)
    : AbstractBufferedOutputStream(stream, bufferSize) {}

uint64_t BufferedOutputStream::Write(const unsigned char* data, uint64_t size) {
  return write(data, size);
}

void BufferedOutputStream::Write(
    const unsigned char* data, uint64_t size,
    const std::function<void(uint64_t)>& onSuccess,
    const std::function<void(const Exception&)>& onFailure) {
  write(data, size, onSuccess, onFailure);
}

uint64_t BufferedOutputStream::Flush() { return flush(); }

void BufferedOutputStream::Flush(
    const std::function<void(uint64_t)>& onSuccess,
    const std::function<void(const Exception&)>& onFailure) {
  flush(onSuccess, onFailure);
}
