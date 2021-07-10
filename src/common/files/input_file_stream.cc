#include "input_file_stream.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

namespace directory_db {
namespace file {

const size_t InputFileStream::kBlockSize = 4096;

InputFileStream InputFileStream::Open(const Path &path)
{
    int fd = open(path.path().data(), O_RDONLY);
    if (fd < 0) {
        throw std::invalid_argument(std::strerror(errno));
    }

    return InputFileStream(fd);
}

InputFileStream::InputFileStream(int fd)
    : fd_(fd)
{
}

InputFileStream::Elem InputFileStream::__next__()
{
    if (fd_ <= 0) {
        throw std::invalid_argument("invalid fd");
    }

    std::string buf;
    buf.resize(kBlockSize);
    ssize_t r = read(fd_, &buf[0], kBlockSize);
    // TODO: not exception
    if (r < 0) {
        throw std::invalid_argument(std::strerror(errno));
    }
    if (r == 0) {
        throw std::out_of_range("");
    }
    buf.resize(r);
    return StringView(std::move(buf));
}

void InputFileStream::Close()
{
    int r = close(fd_);
    if (r < 0) {
        throw std::invalid_argument(std::strerror(errno));
    }
    fd_ = -1;
}


} // namespace file
} // namespace directory_db