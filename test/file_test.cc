#include "src/common/files/file_path.h"
#include "gtest/gtest.h"


namespace directory_db {

TEST(FilePathTest, BasicUsage)
{
    file::Path path("file");
    EXPECT_EQ("file", path.path());
}

} // namespace directory_db