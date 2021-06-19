#pragma once

#include <map>

#include "src/common/directory.pb.h"

namespace directory_db {

using Memtable = std::map<Path, std::string>;

// Flush Memtable into sst file
class TableBuilder {
public:


private:
};

} // namespace directory_db
