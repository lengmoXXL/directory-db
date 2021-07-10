#include "gtest/gtest.h"

#include "src/common/iobuf.h"


namespace directory_db {

TEST(StringViewTest, BasicUsage)
{
    StringView view("abc");

    EXPECT_EQ('a', view[0]);
    EXPECT_EQ('b', view[1]);
    EXPECT_EQ('c', view[2]);

    StringView slice = view.slice(1, 2);
    EXPECT_EQ('b', slice[0]);
    EXPECT_EQ('c', slice[1]);
}

TEST(IOBufTest, BasicUsage)
{
    StringBuf buf;
    buf.Append("abcde");
    EXPECT_EQ(5, util::len(buf));
    EXPECT_EQ("abcde", util::str(buf));
}

} // namespace directory_db
