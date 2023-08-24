#include "InputTest.h"

// Utility function to get all input files from a directory
std::vector<std::string> listInputFiles(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : std::__fs::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".csv" && entry.path().string().find("_case") != std::string::npos) {
            std::cout << entry.path().string() << std::endl;
            files.push_back(entry.path().string());
        }
    }
    return files;
}

// Parameterized test class
class ReadInvalidInputTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST_P(ReadInvalidInputTest, HandlesInvalidInput) {
    std::string testFilePath = GetParam();

    // Check if the function throws an exception for invalid files
    EXPECT_THROW(readInput(testFilePath), std::exception);
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedInvalidTests,
    ReadInvalidInputTest,
    ::testing::ValuesIn(listInputFiles("../tests/unit/readInput/invalid_test_cases/"))
);
