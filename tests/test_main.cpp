#include <gtest/gtest.h>
#include <iostream>
#include "../src/input/readInput.h"
#include "../src/cores/SafeInputTasks.h"
#include "../src/globals/globals.h"
#include <fstream>
#include <vector>
#include <string>

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);    // This test will pass
    EXPECT_TRUE(true);  // This test will also pass
}

// TEST(ReadInputTest, HandlesValidInput) {
//     // Set up a known input file for testing
//     std::string testFilePath = "./valid_input.txt";

//     std::int expectedCount = 3;

//     // read the expected content into a string
//     std::ifstream expectedFile(expectedFilePath);
//     std::string expectedContent((std::istreambuf_iterator<char>(expectedFile)), std::istreambuf_iterator<char>());

//     readInput(testFilePath);

//     // Convert the data stored in global 3D vector into a string
//     std::string producedContent;
//     std::ostringstream oss;


//     // compare the two files to see if they are the same
//     ASSERT_EQ(, ) << "The original and produced contents are not the same!";

// }

// TEST(ReadInputTest, HandlesInvalidInput) {
//     // Test behavior for an invalid/non-existent file
//     EXPECT_THROW(readInput("./tests/non_existent_file.txt"), std::exception);
// }
