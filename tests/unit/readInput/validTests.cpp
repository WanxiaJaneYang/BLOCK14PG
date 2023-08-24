#include "InputTestHelper.h"

// Parameterized test class
class ReadInputTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST_P(ReadInputTest, HandlesValidInput) {

    // Get the expected file path according to the name convention
    std::string testFilePath = GetParam();
    std::string baseName = std::__fs::filesystem::path(testFilePath).stem().string();
        size_t pos = baseName.rfind("_case");
    if (pos != std::string::npos) {
        baseName.erase(pos, 5); // 5 is the length of "_case"
    }
    std::string expectedFilePath = "../tests/unit/readInput/valid_test_cases/" + baseName + "_expected.txt";

    // read the expected content into a string
    std::ifstream expectedFile(expectedFilePath);
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), std::istreambuf_iterator<char>());

    // read the readInput() produced content into a string
    readInput(testFilePath);
    std::string producedContent = writeReadContent();

    // compare the two strings to see if they are the same
    ASSERT_EQ(expectedContent, producedContent) << "The expected and produced contents are not the same!";
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    ReadInputTest,
    ::testing::ValuesIn(listInputFiles("../tests/unit/readInput/valid_test_cases/"))
);