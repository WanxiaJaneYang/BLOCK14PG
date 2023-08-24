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
// Parameterized test class
class ReadInputTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST_P(ReadInputTest, HandlesValidInput) {
    // Get the test file path from the test parameter
    std::string testFilePath = GetParam();

    // Construct the expected file path based on the input file name
    std::string baseName = std::__fs::filesystem::path(testFilePath).stem().string();
        size_t pos = baseName.rfind("_case");
    if (pos != std::string::npos) {
        baseName.erase(pos, 5); // 5 is the length of "_case"
    }
    
    std::string expectedFilePath = "../tests/unit/readInput/valid_test_cases/" + baseName + "_expected.txt";

    // read the expected content into a string
    std::ifstream expectedFile(expectedFilePath);
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), std::istreambuf_iterator<char>());

    readInput(testFilePath);

    // Convert the data stored into a string
    std::ostringstream oss;
    oss << GlobalVars::width << ",";
    oss << GlobalVars::height << ",";
    oss << GlobalVars::depth ;

    // print labels
    for (const auto& pair : GlobalVars::tagTable) {
        oss << "\n" << pair.first << "," << pair.second;
    }

    std::string producedContent = oss.str();

    // Add blocks in tasks to the string
    producedContent.append(GlobalVars::processTasks.writeTasks());

    GlobalVars::processTasks.clearTasks();
    // compare the two files to see if they are the same
    ASSERT_EQ(expectedContent, producedContent) << "The expected and produced contents are not the same!";
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    ReadInputTest,
    ::testing::ValuesIn(listInputFiles("../tests/unit/readInput/valid_test_cases/"))
);