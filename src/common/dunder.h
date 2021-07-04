#pragma once

namespace directory_db {
namespace util {

template<typename T>
size_t len(const T &instance)
{
    return instance.__len__();
}

template<typename T>
std::string str(const T &instance)
{
    return instance.__str__();
}

}
} // namespace directory_db