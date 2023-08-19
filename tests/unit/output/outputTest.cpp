#define BOOST_TEST_MODULE OutputTest
#include <boost/test/included/unit_test.hpp>
#include <fstream>
#include <string>
#include "../../../src/output/output.h"
#include "../../../src/globals/globals.h"

// This test case checks the functionality of the output() function.
BOOST_AUTO_TEST_CASE(test_output_function)
{
    // Set up the tagTable with mappings of characters to their respective string representations.
    GlobalVars::tagTable.insert({'o', "sea"});
    GlobalVars::tagTable.insert({'w', "WA"});
    GlobalVars::tagTable.insert({'n', "NT"});
    GlobalVars::tagTable.insert({'s', "SA"});
    GlobalVars::tagTable.insert({'q', "QLD"});
    GlobalVars::tagTable.insert({'v', "VIC"});
    GlobalVars::tagTable.insert({'t', "TAS"});

    // Specify the name of the output file and call the output() function to generate the file.
    GlobalVars::outputFileName = "output.txt";
    output();

    
    // Open the generated file and read its content. should been no content
    std::ifstream testFile(GlobalVars::outputFileName);
    std::string fileContent;
    std::getline(testFile, fileContent, '\0');
    testFile.close();

    // Check if the content does not contain the string "expected output". the string can set to anyother
    BOOST_CHECK(fileContent.find("expected output") == std::string::npos);
}


// This test case checks the position calculation of a Cuboid.
BOOST_AUTO_TEST_CASE(test_cuboid_position_calculation)
{
    // Create a Cuboid object with specified parameters.
    Cuboid testCuboid(10, 20, 30, 5, 5, 5, 3, 3, 3, 'w');
    GlobalVars::outputTasks.push(testCuboid);

    // Generate the output file.
    GlobalVars::outputFileName = "output_position.txt";
    output();

    // Open the generated file and read its content.
    std::ifstream testFile(GlobalVars::outputFileName);
    std::string fileContent;
    std::getline(testFile, fileContent, '\0');
    testFile.close();

    // Check if the content contains the calculated position "15,25,35".
    BOOST_CHECK(fileContent.find("15,25,35") != std::string::npos);
}

// This test case checks the size attributes of a Cuboid.
BOOST_AUTO_TEST_CASE(test_cuboid_size)
{
    // Create a Cuboid object with specified size parameters.
    Cuboid testCuboid(0, 0, 0, 0, 0, 0, 3, 4, 5, 'o');
    GlobalVars::outputTasks.push(testCuboid);

    // Generate the output file.
    GlobalVars::outputFileName = "output_size.txt";
    output();

    // Open the generated file and read its content.
    std::ifstream testFile(GlobalVars::outputFileName);
    std::string fileContent;
    std::getline(testFile, fileContent, '\0');
    testFile.close();

    // Check if the content contains the size attributes ",3,4,5,".
    BOOST_CHECK(fileContent.find(",3,4,5,") != std::string::npos);
}

// This test case checks the label of a Cuboid.
BOOST_AUTO_TEST_CASE(test_cuboid_label)
{
    // Create a Cuboid object with a specified label.
    Cuboid testCuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 's');
    GlobalVars::outputTasks.push(testCuboid);

    // Generate the output file.
    GlobalVars::outputFileName = "output_label.txt";
    output();

    // Open the generated file and read its content.
    std::ifstream testFile(GlobalVars::outputFileName);
    std::string fileContent;
    std::getline(testFile, fileContent, '\0');
    testFile.close();

    // Check if the content contains the label ",SA".
    BOOST_CHECK(fileContent.find(",SA") != std::string::npos);
}

// This test case checks how the program handles an unknown tag.
// failure is detedted in this function. 
BOOST_AUTO_TEST_CASE(test_unknown_tag)
{
    // 初始化tagTable
    GlobalVars::tagTable.insert({'o', "sea"});
    GlobalVars::tagTable.insert({'w', "WA"});
    GlobalVars::tagTable.insert({'n', "NT"});
    GlobalVars::tagTable.insert({'s', "SA"});
    GlobalVars::tagTable.insert({'q', "QLD"});
    GlobalVars::tagTable.insert({'v', "VIC"});
    GlobalVars::tagTable.insert({'t', "TAS"});

    Cuboid testCuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'x');
    GlobalVars::outputTasks.push(testCuboid);

    // Generate the output file.
    GlobalVars::outputFileName = "output_unknown.txt";
    output();

    // Open the generated file and read its content.
    std::ifstream testFile(GlobalVars::outputFileName);
    std::string fileContent;
    std::getline(testFile, fileContent, '\0');
    testFile.close();
    
    // Check if the content does not contain the unknown tag ",x".
    BOOST_CHECK(fileContent.find(",x") == std::string::npos);
}

// This test case checks the program's behavior with a large number of Cuboid objects.
BOOST_AUTO_TEST_CASE(test_large_number_of_cuboids)
{
    // Create a large number of Cuboid objects.
    for (int i = 0; i < 100; i++)
    {
        Cuboid cuboid(32, 16, 0, i, 7, 0, 2, 1, 1, 'q');
        GlobalVars::outputTasks.push(cuboid);
    }

    // Generate the output file.
    GlobalVars::outputFileName = "output_large.txt";
    output();

    // Open the generated file and read its content.
    std::ifstream testFile(GlobalVars::outputFileName);
    std::string fileContent;
    std::getline(testFile, fileContent, '\0');
    testFile.close();

    // Check if the content contains the tag "QLD".
    BOOST_CHECK(fileContent.find("QLD") != std::string::npos);

    // Verify the position data for each Cuboid.
    for (int i = 0; i < 100; i++)
    {
        int x = 32 + i;
        int y = 16 + 7;
        int z = 0 + 0;
        std::string expectedPositionData = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);
        //check content contains the correct calculated for position 
        BOOST_CHECK(fileContent.find(expectedPositionData) != std::string::npos);
    }
}
