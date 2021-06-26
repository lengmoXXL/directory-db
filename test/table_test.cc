#include "gtest/gtest.h"

#include "src/engine/table.h"
#include "src/engine/table_builder.h"

namespace directory_db {

TEST(TableTest, BasicUsage)
{
    Memtable memtable;
    memtable[MakePath({"p1", "p2"})] = "v1";
    memtable[MakePath({"p1", "p3"})] = "v2";
    memtable[MakePath({"p1", "p4"})] = "v3";
    TableBuilder builder;
    builder.SetLocation("table.sst");
    builder.SetMemtable(memtable);
    builder.Finish();

    Table table = Table::Load("table.sst");
    EXPECT_EQ("v2", table.Get(MakePath({"p1", "p3"})));
}

} // namespace directory_db