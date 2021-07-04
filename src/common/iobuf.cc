#include "iobuf.h"

#include <algorithm>
#include <sstream>


namespace directory_db {

void IOBuf::Append(const std::string &data)
{
    if (blocks_.empty()) {
        blocks_.emplace_back(new Block);
        blocks_.back()->reserve(kBlockSize);
    }

    for (size_t pos = 0; pos < data.size(); ) {
        Block &last = *blocks_.back();
        size_t remaining = std::min(kBlockSize - last.size(),
                                    data.size() - pos);
        last.append(&data[pos], remaining);
        pos += remaining;
        if (last.size() == kBlockSize) {
            blocks_.emplace_back(new Block);
            blocks_.back()->reserve(kBlockSize);
        }
    }
}

size_t IOBuf::__len__() const
{
    if (blocks_.empty()) {
        return 0;
    }
    return kBlockSize * (blocks_.size() - 1) + blocks_.back()->size();
}

std::string IOBuf::__str__() const
{
    std::stringstream os;
    for (const BlockRef &ref: blocks_) {
        os << *ref;
    }
    return os.str();
}


} // namespace directory_db