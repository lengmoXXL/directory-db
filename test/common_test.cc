#include "gtest/gtest.h"

#include "src/common/directory.pb.h"

namespace directory_db {

TEST(DirectoryTest, BasicUsage)
{
    Path path;
    path.add_parts("abc");
    path.add_parts("cde");
    EXPECT_EQ(2, path.parts_size());
}

}