#include <gtest/gtest.h>
#include <iostream>
#include "../../../src/input/readInput.h"
#include "../../../src/cores/SafeInputTasks.h"
#include "../../../src/globals/globals.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

TEST(ReadInputTest, HandlesValidInput) {
    // Set up a known input file for testing
    std::string testFilePath = "../tests/unit/readInput/test_cases/input1_case.txt";

    // std::int expectedCount = 0;
    std::string expectedFilePath = "../tests/unit/readInput/test_cases/input1_expected.txt";

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
        oss << "\n"<< pair.first << "," << pair.second  ;
    }

    std::string producedContent = oss.str();

    // Add blocks in tasks to the string
    producedContent.append(GlobalVars::processTasks.writeTasks());

    // compare the two files to see if they are the same
    ASSERT_EQ(expectedContent,producedContent ) << "The expected and produced contents are not the same!";

}

TEST(ReadInputTest, HandlesInvalidInput) {
    // Test behavior for an invalid file
    EXPECT_THROW(readInput("../tests/unit/readInput/test_cases/input2_case.txt"), std::exception);
}
