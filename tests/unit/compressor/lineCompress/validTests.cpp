#include "Helper.h"

// Parameterized test class
class LineCompressTest : public ::testing::TestWithParam<std::string>
{
};

// Actual test definition
TEST_P(LineCompressTest, HandlesValidCompression)
{

  // Get the expected file path according to the naming convention
  std::string testFilePath = GetParam();

  // Read the content of the file into an istringstream
  std::ifstream inFile(testFilePath);
  std::stringstream buffer;
  buffer << inFile.rdbuf();
  std::istringstream simulatedInput(buffer.str());

  Block testBlock = createBlockFromInputFile(testFilePath);

  // Call the lineCompress function with the simulated input
  auto compressedResult = lineCompress(testBlock);

  std::string producedContent = writeCompressedResult(compressedResult);

  // Determine the expected result file path
  std::string baseName = std::filesystem::path(testFilePath).stem().string();
  size_t pos = baseName.rfind("_case");
  if (pos != std::string::npos)
  {
    baseName.erase(pos, 5); // 5 is the length of "_case"
  }
  std::string expectedFilePath = "../../tests/unit/compressor/lineCompress/valid_test_cases/" + baseName + "_expected.txt";

  // Read the expected content into a string
  std::ifstream expectedFile(expectedFilePath);
  std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), std::istreambuf_iterator<char>());

  // Compare the two strings to see if they are the same
  ASSERT_EQ(expectedContent, producedContent) << "The expected and produced contents are not the same!";
}

// Instantiate the test case with the files in the directory
INSTANTIATE_TEST_SUITE_P(
    FileBasedTests,
    LineCompressTest,
    ::testing::ValuesIn(listInputFiles("../../tests/unit/compressor/lineCompress/valid_test_cases/")));