#pragma once

#include <vector>
#include <array>
#include <memory>

#include "dunder.h"

namespace directory_db {

class IOBuf {
public:
    static constexpr size_t kBlockSize = 1024;
public:
    void Append(const std::string &data);

    size_t __len__() const;
    std::string __str__() const;

private:
    using Block = std::string;
    using BlockRef = std::shared_ptr<Block>;

private:
    std::vector<BlockRef> blocks_;
};

} // namespace directory_db