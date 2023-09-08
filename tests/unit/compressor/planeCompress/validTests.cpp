#include "planeCompressTestHelper.h"

// Parameterized test class
class PlaneCompressTest : public ::testing::TestWithParam<std::string>
{
};

// Actual test definition
TEST_P(PlaneCompressTest, HandlesValidInput)
{
    // Get the expected file path according to the name convention
    std::string testFilePath = GetParam();

    // Read the content of the file into an istringstream
    std::ifstream inFile(testFilePath);
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();

    // Convert file content to the required data structure
    std::deque<std::deque<std::deque<Cuboid>>> lines = convertFileContentToLines(fileContent);

    // Read the planeCompress() produced content into a string
    std::deque<std::deque<Cuboid>> plane = planeCompress(lines);

    std::string producedContent = writeReadContent(plane); // method to generate output to string

    // find the expected result
    std::string baseName = std::__fs::filesystem::path(testFilePath).stem().string();
    size_t pos = baseName.rfind("_case");
    if (pos != std::string::npos)
    {
        baseName.erase(pos, 5); // 5 is the length of "_case"
    }

    std::string expectedFilePath = "../../tests/unit/compressor/planeCompress/valid_test_cases/" + baseName + "_expected.txt";

    // read the expected content into a string
    std::ifstream expectedFile(expectedFilePath);
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), std::istreambuf_iterator<char>());

    // compare the two strings to see if they are the same
    ASSERT_EQ(expectedContent, producedContent) << "The expected and produced contents are not the same!";
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    PlaneCompressTest,
    ::testing::ValuesIn(listInputFiles("../../tests/unit/compressor/planeCompress/valid_test_cases/")));