#include "InputTestHelper.h"

// Parameterized test class
class ReadInvalidInputTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST_P(ReadInvalidInputTest, HandlesInvalidInput) {
    
    // Get the test file path found
    std::string testFilePath = GetParam();
    // Read the content of the file into an istringstream
    std::ifstream inFile(testFilePath);
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::istringstream simulatedInput(buffer.str());

    // Check if the function throws an exception for invalid files
    EXPECT_THROW(readInput(simulatedInput), std::exception);
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedInvalidTests,
    ReadInvalidInputTest,
    ::testing::ValuesIn(listInputFiles("../../tests/unit/readInput/invalid_test_cases/"))
);
