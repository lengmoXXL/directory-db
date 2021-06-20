#include "gtest/gtest.h"

#include "src/engine/table_builder.h"

namespace directory_db {

Path MakePath(const std::vector<std::string> &parts)
{
    Path ret;
    for (const std::string &part: parts) {
        ret.add_parts(part);
    }
    return ret;
}

TEST(TableBuilderTest, InsertItem)
{
    TableBuilder builder;
    builder.SetLocation("table.sst")
           .InsertItem(MakePath({"a", "b", "c"}), "value1")
           .InsertItem(MakePath({"a", "b", "d"}), "value2")
           .Finish();
}

TEST(TableBuilderTest, SetMemtable)
{
    Memtable table;
    table[MakePath({"a", "b", "c"})] = "value1";
    table[MakePath({"a", "b", "b"})] = "value1";

    TableBuilder builder;
    builder.SetLocation("table.sst")
           .SetMemtable(table)
           .Finish();
}


} // namespace directory_db