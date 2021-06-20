#pragma once

#include <map>

#include "boost/iostreams/device/file.hpp"
#include "boost/iostreams/stream.hpp"

#include "src/common/directory.pb.h"

namespace directory_db {

struct PathCmp {
    bool operator() (const Path &a, const Path b) {
        for (int i = 0; i < a.parts_size() && i < b.parts_size(); ++ i) {
            int r = a.parts(i).compare(b.parts(i));
            if (r != 0) {
                return r < 0;
            }
        }
        return a.parts_size() < b.parts_size();
    }
};

namespace io = boost::iostreams;
using Value = std::string;
using Memtable = std::map<Path, std::string, PathCmp>;

// Flush Memtable into sst file
class TableBuilder {
public:
    TableBuilder();
    ~TableBuilder();

    TableBuilder &SetLocation(const std::string &fs_path);
    TableBuilder &SetMemtable(const Memtable &table);
    TableBuilder &InsertItem(const Path &path, const Value &value);
    void Finish();

private:
    io::stream_buffer<io::file_sink> *buf_{nullptr};
    std::ostream *stream_{nullptr};
};


} // namespace directory_db
