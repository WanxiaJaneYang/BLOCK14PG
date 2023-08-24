#include "input_test.h"

// Utility function to get all input files from a directory
std::vector<std::string> listInputFiles(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : std::__fs::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".csv" && entry.path().string().find("_case.txt") != std::string::npos) {
            std::cout<<entry.path().string()<<std::endl;
            files.push_back(entry.path().string());
        }
    }
    return files;
}
class ReadInvalidInputTest : public ::testing::TestWithParam<std::string> {};

TEST_P(ReadInvalidInputTest, HandlesInvalidInput) {
    std::string testFilePath = GetParam();

    // Check if the function throws an exception for invalid files
    EXPECT_THROW(readInput(testFilePath), std::exception);
}

INSTANTIATE_TEST_SUITE_P(
    FileBasedInvalidTests,
    ReadInvalidInputTest,
    ::testing::ValuesIn(listInputFiles("../tests/unit/readInput/invalid_test_cases/"))
);
