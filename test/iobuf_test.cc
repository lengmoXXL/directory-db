#include "gtest/gtest.h"

#include "src/common/iobuf.h"


namespace directory_db {

TEST(IOBufTest, BasicUsage)
{
    IOBuf buf;
    buf.Append("abcde");
    EXPECT_EQ(5, util::len(buf));
    EXPECT_EQ("abcde", util::str(buf));
}

} // namespace directory_db
