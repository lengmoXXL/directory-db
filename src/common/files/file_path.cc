#include "file_path.h"


namespace directory_db {
namespace file {

Path::Path(const std::string &path): path_(path)
{
}

std::string Path::path()
{
    return path_;
}

} // namespace file 
} // namespace directory_db