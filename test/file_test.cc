#include "gtest/gtest.h"

#include "src/common/dunder.h"
#include "src/common/files/file_path.h"
#include "src/common/files/input_file_stream.h"
#include "src/common/files/output_file_stream.h"

namespace directory_db {

TEST(FilePathTest, BasicUsage)
{
    file::Path path("file");
    EXPECT_EQ("file", path.path());
}

TEST(InputFileStreamTest, BasicUsage)
{
    file::Path path("/dev/zero");
    file::InputFileStream input = file::InputFileStream::Open(path);
    StringView view = util::next(input);
    for (size_t i = 0; i < util::len(view); ++ i) {
        EXPECT_EQ('\0', view[i]);
    }
    EXPECT_GT(util::len(view), 0) << util::len(view);
}

TEST(OutputFileStreamTest, BasicUsage)
{
    file::Path path("file");
    {
        file::OutputFileStream output = file::OutputFileStream::Open(path);
        output << StringView("abc");
        output.Close();
    }
    {
        file::InputFileStream input = file::InputFileStream::Open(path);
        StringView view = util::next(input);
        EXPECT_EQ(3, util::len(view));
        EXPECT_EQ("abc", util::str(view));
    }
}

TEST(InputOutputStreamTest, InvalidFd)
{
    file::Path path("file");
    {
        file::OutputFileStream output = file::OutputFileStream::Open(path);
        output << StringView("aaa");
        output << StringView("\nbbb");
        output.Close();
        EXPECT_THROW(output << StringView("\nccc"), std::invalid_argument);
    }
    {
        file::InputFileStream input = file::InputFileStream::Open(path);
        StringView view = util::next(input);
        input.Close();
        EXPECT_THROW(util::next(input), std::invalid_argument);
    }
}

} // namespace directory_db