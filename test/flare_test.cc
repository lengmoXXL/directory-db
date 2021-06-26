#include "gtest/gtest.h"
#include "boost/asio/io_context.hpp"
#include "boost/asio/post.hpp"

#include "src/common/data_model.h"

namespace directory_db {

TEST(DirectoryTest, Flare)
{
    PathPB path;
    path.add_parts("abc");
    path.add_parts("cde");
    EXPECT_EQ(2, path.parts_size());
}

TEST(AsioTest, Flare)
{
    using boost::asio::io_context;
    using boost::asio::post;

    io_context ctx;
    int cnt = 0;
    
    post(ctx, [&cnt]{ ++ cnt;});
    ctx.run();
    EXPECT_EQ(1, cnt);
}

}