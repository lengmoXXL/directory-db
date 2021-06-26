#pragma once

#include <map>
#include <string>

#include "src/common/data_model.h"

namespace directory_db {

struct PathCmp {
    bool operator() (const PathPB &a, const PathPB b) {
        for (int i = 0; i < a.parts_size() && i < b.parts_size(); ++ i) {
            int r = a.parts(i).compare(b.parts(i));
            if (r != 0) {
                return r < 0;
            }
        }
        return a.parts_size() < b.parts_size();
    }
};

using Value = std::string;
using Memtable = std::map<PathPB, std::string, PathCmp>;

class Table {
public:
    static Table Load(const std::string &file);

    ~Table();
    Value Get(const PathPB &path);

private:
    Table();
    Table(const Memtable &memtable);
    Table(Memtable &&memtable);
    Memtable memtable_;
};

} // namespace directory_db