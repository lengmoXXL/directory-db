#include "table_builder.h"

namespace directory_db {

TableBuilder::TableBuilder()
{
}

TableBuilder::~TableBuilder()
{
    delete stream_;
    delete buf_;
}

TableBuilder &TableBuilder::SetLocation(const std::string &fs_path)
{
    buf_ = new io::stream_buffer<io::file_sink>(fs_path);
    stream_ = new std::ostream(buf_);
    if (stream_->bad()) {
        throw std::invalid_argument("failed to open file");
    }
    return *this;
}

TableBuilder &TableBuilder::SetMemtable(const Memtable &table)
{
    for (const auto &p: table) {
        if (!p.first.SerializePartialToOstream(stream_)) {
            throw std::invalid_argument("failed to serialize");
        }
        *stream_ << ":" << p.second;
    }
    if (stream_->bad()) {
        throw std::invalid_argument("bad stream");
    }
    return *this;
}

TableBuilder &TableBuilder::InsertItem(const Path &path, const Value &value)
{
    if (!path.SerializePartialToOstream(stream_)) {
        throw std::invalid_argument("failed to serialize");
    }
    *stream_ << ":" << value;
    if (stream_->bad()) {
        throw std::invalid_argument("bad stream");
    }
    return *this;
}

void TableBuilder::Finish()
{
    stream_->flush();
    if (stream_->bad()) {
        throw std::invalid_argument("failed to flush");
    }
}


} // namespace directory_db