#include "IntegrationTestHelper.h"

// Parameterized test class
class IntegrationTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST_P(IntegrationTest, HandlesValidIntegration) {

    // Get the expected file path according to the name convention
    std::string testFilePath = GetParam();

    // Read the content of the file into an istringstream
    std::istringstream simulatedInput = simulateInputStream(testFilePath);

    readInput(simulatedInput); 
    Compressor::compress(); 

    // Redirect std::cout to oss
    std::ostringstream oss;
    StreamRedirector redirect(std::cout, oss.rdbuf());
        
    // Call the output function
    output();
    
    // Split the output into lines and sort them
    std::istringstream iss(oss.str());
    std::vector<std::string> ProducedLines = sortedLinesFromStream(iss);

    // find the expected result
    std::string baseName = std::__fs::filesystem::path(testFilePath).stem().string();
        size_t pos = baseName.rfind("_case");
    if (pos != std::string::npos) {
        baseName.erase(pos, 5); // 5 is the length of "_case"
    }
    std::string expectedFilePath = "../../tests/integration/valid_test_cases/" + baseName + "_expected.txt";

    // convert the file stream into sorted lines
    std::ifstream expectedFile(expectedFilePath);
    std::vector<std::string> expectedLines = sortedLinesFromStream(expectedFile);

    // compare the two strings to see if they are the same
    ASSERT_EQ(expectedLines, ProducedLines) << "The expected and produced contents are not the same!";
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    IntegrationTest,
    ::testing::ValuesIn(listInputFiles("../../tests/integration/valid_test_cases/"))
);