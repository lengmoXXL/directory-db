#pragma once

#include "file_path.h"
#include "src/common/iobuf.h"

namespace directory_db {
namespace file {

class InputFileStream
{
public:
    using Elem = StringView;

    static const size_t kBlockSize;

public:
    static InputFileStream Open(const Path &path);
    Elem __next__();
    void Close();

private:
    InputFileStream(int fd);

    int fd_{-1};
};

} // namespace file
} // namespace directory_db