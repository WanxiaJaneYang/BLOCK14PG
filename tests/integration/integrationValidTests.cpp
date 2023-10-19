#include "IntegrationTestHelper.h"

// Parameterized test class
// class IntegrationTest : public ::testing::TestWithParam<std::string> {};

// Actual test definition
TEST(Singletest, HandlesValidIntegration)
{

    // // Get the expected file path according to the name convention
    // std::string testFilePath = GetParam();

    // // Read the content of the file into an istringstream
    // std::istringstream simulatedInput = simulateInputStream(testFilePath);

    // Redirect std::cout to oss
    std::ostringstream oss;
    StreamRedirector redirect(std::cout, oss.rdbuf());

    startThreads();
    // readInput(simulatedInput);
    // Compressor::compress();
    // output();

    std::istringstream iss(oss.str());
    std::string outputPath = "../../tests/integration/valid_test_cases/_outcome.txt";
    std::ofstream outFile(outputPath);

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open the output file!" << std::endl;
        return; // Exit the function or handle the error as appropriate
    }

    std::string line;
    while (std::getline(iss, line))
    {
        outFile << line << std::endl;
    }

    outFile.close(); // Close the file before checking its size
    ASSERT_FALSE(std::__fs::filesystem::file_size(outputPath) == 0) << "Output file is empty!";
}

// // Instantiate the test case with the files in the directory
// INSTANTIATE_TEST_SUITE_P(
//     FileBasedTests,
//     IntegrationTest,
//     ::testing::ValuesIn(listInputFiles("../../tests/integration/valid_test_cases/"))
// );