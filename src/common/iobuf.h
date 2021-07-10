#pragma once

#include <vector>
#include <array>
#include <memory>
#include <sstream>

#include "dunder.h"

namespace directory_db {

class StringView {
public:
    StringView(const std::string &s);
    StringView(const char *data);
    StringView(std::string &&s);

    StringView slice(int64_t start, int64_t limit) const;

    const char *data() const;

    char operator[](int idx) const;
    size_t __len__() const;
    std::string __str__() const;

private:
    int64_t start_{0};
    int64_t limit_{0};
    std::shared_ptr<std::string> ref_;
};

inline std::ostream& operator<<(std::ostream &os, const StringView &view)
{
    for (size_t i = 0; i < util::len(view); ++ i) {
        os << view[i];
    }
    return os;
}

class StringBuf {
public:
    void Append(const std::string &data);

    size_t __len__() const;
    std::string __str__() const;

private:
    std::vector<StringView> buf_;
    int64_t length_{0};
};

} // namespace directory_db