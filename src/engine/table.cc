#include "table.h"

#include "boost/iostreams/device/file.hpp"
#include "boost/iostreams/stream.hpp"

namespace directory_db {

Table Table::Load(const std::string &file)
{
    using boost::iostreams::file_source;
    using boost::iostreams::stream_buffer;

    Memtable memtable;
    DirectoryDataBasePB db;

    stream_buffer<file_source> buf(file);
    std::istream is(&buf);
    if (!db.ParseFromIstream(&is)) {
        throw std::invalid_argument("failed to load file: " + file);
    }

    for (const DirectoryPB &dir: db.directories()) {
        memtable[dir.path()] = dir.value();
    }
    return Table(std::move(memtable));
}

Table::~Table()
{
}

Value Table::Get(const PathPB &path)
{
    return memtable_[path];
}

Table::Table()
{
}

Table::Table(const Memtable &memtable)
    : memtable_(memtable)
{
}

Table::Table(Memtable &&memtable)
    : memtable_(std::move(memtable))
{
}

} // namespace directory_db