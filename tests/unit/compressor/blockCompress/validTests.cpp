#include "blockCompressTestHelper.h"

// Parameterized test class
class BlockCompressTest : public ::testing::TestWithParam<std::string>
{
};

// Actual test definition
TEST_P(BlockCompressTest, HandlesValidInput)
{
    // Get the expected file path according to the name convention
    std::string testFilePath = GetParam();

    // Read the content of the file into an istringstream
    std::ifstream inFile(testFilePath);
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();

    // Convert file content to the required data structure
    std::deque<std::deque<Cuboid>> planes = convertFileContentToPlanes(fileContent);

    // Read the blockCompress() produced content into a string
    blockCompress(planes);

    std::string producedContent = writeReadContent(); // method to generate output to string

    // find the expected result
    std::string baseName = std::__fs::filesystem::path(testFilePath).stem().string();
    size_t pos = baseName.rfind("_case");
    if (pos != std::string::npos)
    {
        baseName.erase(pos, 5); // 5 is the length of "_case"
    }

    std::string expectedFilePath = "../../tests/unit/compressor/blockCompress/valid_test_cases/" + baseName + "_expected.txt";

    // read the expected content into a string
    std::ifstream expectedFile(expectedFilePath);
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), std::istreambuf_iterator<char>());

    // compare the two strings to see if they are the same
    ASSERT_EQ(expectedContent, producedContent) << "The expected and produced contents are not the same!";
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    BlockCompressTest,
    ::testing::ValuesIn(listInputFiles("../../tests/unit/compressor/blockCompress/valid_test_cases/")));