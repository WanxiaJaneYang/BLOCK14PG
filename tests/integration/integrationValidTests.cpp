#include "IntegrationTestHelper.h"

// Actual test definition
TEST(Singletest, HandlesValidIntegration)
{
    // Redirect std::cout to oss
    std::ostringstream oss;
    StreamRedirector redirect(std::cout, oss.rdbuf());

    startThreads();

    std::istringstream iss(oss.str());
    std::string outputPath = "../../tests/integration/valid_test_cases/_outcome.txt";
    std::ofstream outFile(outputPath);

    if (!outFile.is_open())
    {
        std::cerr << "Failed to open the output file!" << std::endl;
        return; // Exit the function or handle the error as appropriate
    }

    if (oss.str().empty())
    {
        std::cerr << "No data to write!" << std::endl;
    }
    std::string line;
    while (std::getline(iss, line))
    {
        outFile << line << std::endl;
        outFile.flush(); // Force the buffer to flush to the file
    }

    outFile.close(); // Close the file before checking its size
    ASSERT_FALSE(std::__fs::filesystem::file_size(outputPath) == 0) << "Output file is empty!";
}
// ASSERT_FALSE(1 == 0) << "Output file is empty!";
