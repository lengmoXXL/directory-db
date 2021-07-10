#pragma once

#include "file_path.h"
#include "src/common/iobuf.h"
#include "src/common/dunder.h"

namespace directory_db {
namespace file {

class OutputFileStream {
public:
    static OutputFileStream Open(const Path &path);

    void Write(const StringView &view);
    void Close();

private:
    OutputFileStream(int fd);

    int fd_{-1};
};

template<typename T>
OutputFileStream& operator<<(OutputFileStream &os, const T &instance)
{
    os.Write(util::str(instance));
    return os;
}

} // namespace file
} // namespace directory_db