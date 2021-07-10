#include "iobuf.h"

#include <algorithm>


namespace directory_db {

StringView::StringView(const std::string &s)
    : ref_(std::make_shared<std::string>(s))
{
    limit_ = (*ref_).size();
}

StringView::StringView(const char *data)
    : ref_(std::make_shared<std::string>(data))
{
    limit_ = (*ref_).size();
}

StringView::StringView(std::string &&s)
    : ref_(std::make_shared<std::string>(std::move(s)))
{
    limit_ = (*ref_).size();
}

StringView StringView::slice(int64_t start, int64_t limit) const
{
    StringView ret(*ref_);
    ret.start_ = start;
    ret.limit_ = limit;
    return ret;
}

const char* StringView::data() const
{
    return &(*ref_)[start_];
}

char StringView::operator[](int idx) const
{
    return (*ref_)[start_ + idx];
}

size_t StringView::__len__() const
{
    return limit_ - start_;
}

std::string StringView::__str__() const
{
    return (*ref_).substr(start_, limit_ - start_);
}

// IOBuf

void StringBuf::Append(const std::string &data)
{
    buf_.emplace_back(data);
    length_ += data.size();
}

size_t StringBuf::__len__() const
{
    return length_;
}

std::string StringBuf::__str__() const
{
    std::stringstream os;
    for (const StringView &view: buf_)
    {
        os << view;
    }
    return os.str();
}


} // namespace directory_db