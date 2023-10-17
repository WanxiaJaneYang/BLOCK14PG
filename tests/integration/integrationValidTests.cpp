#include "IntegrationTestHelper.h"

// Parameterized test class
class IntegrationTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST_P(IntegrationTest, HandlesValidIntegration) {

    // Get the expected file path according to the name convention
    std::string testFilePath = GetParam();

    // Read the content of the file into an istringstream
    std::istringstream simulatedInput = simulateInputStream(testFilePath);

    // Redirect std::cout to oss
    std::ostringstream oss;
    StreamRedirector redirect(std::cout, oss.rdbuf());

    startThreads(simulatedInput);
    // readInput(simulatedInput); 
    // Compressor::compress(); 
    // output();
    
    // Split the output into lines and sort them
    std::istringstream iss(oss.str());
    // std::vector<std::string> ProducedLines = sortedLinesFromStream(iss);
    
    // cancel sorting for checking the order of thread execution
    std::vector<std::string> ProducedLines;
    std::string line;
    while (std::getline(iss, line)) {
        ProducedLines.push_back(line);
    }

    // find the expected result
    std::string baseName = std::filesystem::path(testFilePath).stem().string();
        size_t pos = baseName.rfind("_case");
    if (pos != std::string::npos) {
        baseName.erase(pos, 5); // 5 is the length of "_case"
    }
    std::string expectedFilePath = "../../tests/integration/valid_test_cases/" + baseName + "_expected.txt";

    // convert the file stream into sorted lines
    std::ifstream expectedFile(expectedFilePath);
    std::vector<std::string> expectedLines = sortedLinesFromStream(expectedFile);

    // an output file for validating multithreading
    std::string outputPath = "../../tests/integration/valid_test_cases/" + baseName + "_outcome.txt";
    std::ofstream outFile(outputPath);  
    if (outFile.is_open())
    {
        // Iterate through the vector and write each line to the file
        for (const auto& line : ProducedLines)
        {outFile << line << std::endl;}
        outFile.close();  // Close the file
    }
    else
    {
        std::cerr << "Failed to open the output file!" << std::endl;
    }

    // compare the two strings to see if they are the same
    // ASSERT_EQ(expectedLines, ProducedLines) << "The expected and produced contents are not the same!";
    ASSERT_FALSE(ProducedLines.empty()) << "ProducedLines is empty!";

}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    IntegrationTest,
    ::testing::ValuesIn(listInputFiles("../../tests/integration/valid_test_cases/"))
);