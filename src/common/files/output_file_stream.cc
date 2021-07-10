#include "output_file_stream.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace directory_db {
namespace file {

OutputFileStream OutputFileStream::Open(const Path &path)
{
    int fd = open(path.path().data(), O_WRONLY | O_CREAT);
    if (fd < 0) {
        throw std::invalid_argument(std::strerror(errno));
    }

    return OutputFileStream(fd);
}


void OutputFileStream::Write(const StringView &view)
{
    if (fd_ <= 0) {
        throw std::invalid_argument("invalid fd");
    }

    const char *begin = view.data();
    size_t length = util::len(view);
    for (size_t bytes_written = 0; bytes_written < length; ) {
        size_t r = write(fd_, begin+bytes_written, length - bytes_written);
        if (r < 0) {
            throw std::invalid_argument(std::strerror(errno));
        }
        bytes_written += r;
    }
}

void OutputFileStream::Close()
{
    int r = close(fd_);
    if (r < 0) {
        throw std::invalid_argument(std::strerror(errno));
    }
    fd_ = -1;
}

OutputFileStream::OutputFileStream(int fd)
    : fd_(fd)
{
}


}
} // namespace directory_db