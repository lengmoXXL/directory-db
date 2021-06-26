#pragma once

#include <vector>

#include "src/common/data_model.pb.h"

namespace directory_db {

PathPB MakePath(const std::vector<std::string> &parts)
{
    PathPB ret;
    for (const std::string &part: parts) {
        ret.add_parts(part);
    }
    return ret;
}

} // namespace directory_db
