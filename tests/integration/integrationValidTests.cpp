#include "IntegrationTestHelper.h"

// Parameterized test class
class IntegrationTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST_P(IntegrationTest, HandlesValidIntegration) {

    // Get the expected file path according to the name convention
    std::string testFilePath = GetParam();

    // Read the content of the file into an istringstream
    std::ifstream inFile(testFilePath);

    // simulate input stream
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::istringstream simulatedInput(buffer.str());
    std::cerr << "simulated input "<< std::endl;

    readInput(simulatedInput); 
    std::cerr << "input finished" << std::endl;
    Compressor::compress(); 
    std::cerr << "compression finished" << std::endl;

    // Redirect std::cout to a stringstream
    std::ostringstream oss;
    std::streambuf* pbuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    // Call the output function
    output();
    std::cerr << "output finished" << std::endl;

    // Restore std::cout
    std::cout.rdbuf(pbuf);
    
    // Split the output into lines and sort them
    std::istringstream iss(oss.str());
    std::vector<std::string> ProducedLines;
    std::string line;
    while (std::getline(iss, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        ProducedLines.push_back(line);
    }
    std::sort(ProducedLines.begin(), ProducedLines.end());  

    // find the expected result
    std::string baseName = std::__fs::filesystem::path(testFilePath).stem().string();
        size_t pos = baseName.rfind("_case");
    if (pos != std::string::npos) {
        baseName.erase(pos, 5); // 5 is the length of "_case"
    }
    std::string expectedFilePath = "../../tests/integration/valid_test_cases/" + baseName + "_expected.txt";

    // Convert expectedContent into a vector of lines
    std::ifstream expectedFile(expectedFilePath);
    std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), std::istreambuf_iterator<char>());
    std::istringstream expectedStream(expectedContent);
    std::vector<std::string> expectedLines;
    while (std::getline(expectedStream, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        expectedLines.push_back(line);
    }
    std::sort(expectedLines.begin(), expectedLines.end());

    // compare the two strings to see if they are the same
    ASSERT_EQ(expectedLines, ProducedLines) << "The expected and produced contents are not the same!";
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    IntegrationTest,
    ::testing::ValuesIn(listInputFiles("../../tests/integration/valid_test_cases/"))
);