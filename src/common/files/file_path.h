#pragma once

#include <vector>
#include <string>

namespace directory_db {
namespace file {

class Path
{
public:
    Path(const std::string &path);

    std::string path();
private:
    std::string path_;
};

}
} // namespace directory_db