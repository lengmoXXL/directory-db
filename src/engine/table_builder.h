#pragma once

#include <map>

#include "boost/iostreams/device/file.hpp"
#include "boost/iostreams/stream.hpp"

#include "src/common/data_model.h"
#include "table.h"

namespace directory_db {

namespace io = boost::iostreams;

// Flush Memtable into sst file
class TableBuilder {
public:
    TableBuilder();
    ~TableBuilder();

    TableBuilder &SetLocation(const std::string &fs_path);
    TableBuilder &SetMemtable(const Memtable &table);
    TableBuilder &InsertItem(const PathPB &path, const Value &value);
    void Finish();

private:
    io::stream_buffer<io::file_sink> *buf_{nullptr};
    std::ostream *stream_{nullptr};
};


} // namespace directory_db
