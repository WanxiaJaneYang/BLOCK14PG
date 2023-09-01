#include "IntegrationTestHelper.h"

// Parameterized test class
class ReadInputTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST_P(IntegrationTest, HandlesValidInput) {

    // Get the expected file path according to the name convention
    std::string testFilePath = GetParam();

    // Read the content of the file into an istringstream
    std::ifstream inFile(testFilePath);
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::istringstream simulatedInput(buffer.str());

    // startThread()
    readInput(simulatedInput); // change to use std::istringstream as input type
    Compressor::compress();

    // Redirect std::cout to a stringstream
    std::ostringstream oss;
    std::streambuf* pbuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Call the output function
    output();

    // Restore std::cout
    std::cout.rdbuf(pbuf);
    std::istringstream iss(oss.str());
    std::string producedContent = iss.str();

    // find the expected result
    std::string baseName = std::__fs::filesystem::path(testFilePath).stem().string();
        size_t pos = baseName.rfind("_case");
    if (pos != std::string::npos) {
        baseName.erase(pos, 5); // 5 is the length of "_case"
    }
    std::string expectedFilePath = "../../tests/integration/valid_test_cases/" + baseName + "_expected.txt";

    // read the expected content into a string
    std::ifstream expectedFile(expectedFilePath);
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), std::istreambuf_iterator<char>());

    // compare the two strings to see if they are the same
    ASSERT_EQ(expectedContent, producedContent) << "The expected and produced contents are not the same!";
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    IntegrationTest,
    ::testing::ValuesIn(listInputFiles("../../tests/integration/valid_test_cases/"))
);