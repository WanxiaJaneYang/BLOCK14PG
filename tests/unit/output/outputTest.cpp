#define BOOST_TEST_MODULE OutputTest
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include "../../../src/output/output.h"
#include "../../../src/globals/globals.h"

BOOST_AUTO_TEST_CASE(test_empty_outputTasks)
{
    // Redirect std::cout to a stringstream
    std::ostringstream oss;
    std::streambuf* pbuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Call the output function
    output();

    // Restore std::cout
    std::cout.rdbuf(pbuf);

    // Verify the output is empty
    BOOST_CHECK_EQUAL(oss.str(), "");
}

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
    
    // Initialize a Cuboid for testing
    Cuboid testCuboid(1, 2, 3, 4, 5, 6, 7, 8, 9, 'o');
    GlobalVars::outputTasks.push(testCuboid);

    // Redirect std::cout to a stringstream
    std::ostringstream oss;
    std::streambuf* pbuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Call the output function
    output();

    // Restore std::cout
    std::cout.rdbuf(pbuf);

    // Verify the output
    std::string expectedOutput = "5, 7, 9, 7, 8, 9, sea\n";
    BOOST_CHECK_EQUAL(oss.str(), expectedOutput);    
}

BOOST_AUTO_TEST_CASE(test_tag)
{
    GlobalVars::tagTable.insert({'o', "sea"});
    GlobalVars::tagTable.insert({'w', "WA"});
    GlobalVars::tagTable.insert({'n', "NT"});
    GlobalVars::tagTable.insert({'s', "SA"});
    GlobalVars::tagTable.insert({'q', "QLD"});
    GlobalVars::tagTable.insert({'v', "VIC"});
    GlobalVars::tagTable.insert({'t', "TAS"});
    // Initialize a Cuboid with an unknown tag
    Cuboid testCuboid(1, 1, 1, 1, 1, 1, 1, 1, 1, 't');
    GlobalVars::outputTasks.push(testCuboid);

    // Redirect std::cout to a stringstream
    std::ostringstream oss;
    std::streambuf* pbuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Call the output function
    output();

    // Restore std::cout
    std::cout.rdbuf(pbuf);

    // Verify the output (depends on how you handle unknown tags)
    // For this example, let's assume an unknown tag outputs "UNKNOWN"
    std::string expectedOutput = "2, 2, 2, 1, 1, 1, TAS\n";
    BOOST_CHECK_EQUAL(oss.str(), expectedOutput);
}

BOOST_AUTO_TEST_CASE(test_multiple_cuboids)
{
    // Initialize multiple Cuboids
    Cuboid cuboid1(1, 1, 1, 1, 1, 1, 1, 1, 1, 'o');
    Cuboid cuboid2(2, 2, 2, 2, 2, 2, 2, 2, 2, 'w');
    GlobalVars::outputTasks.push(cuboid1);
    GlobalVars::outputTasks.push(cuboid2);

    // Redirect std::cout to a stringstream
    std::ostringstream oss;
    std::streambuf* pbuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Call the output function
    output();

    // Restore std::cout
    std::cout.rdbuf(pbuf);

    // mul-thread test:
    // Verify the output contains both Cuboids
    // std::string expectedOutput = "2, 3, 3, 2, 2, 2, WA\n2, 2, 2, 1, 1, 1, sea\n";
    // BOOST_CHECK_EQUAL(oss.str(), expectedOutput);

    // Split the output into lines and sort them
    std::istringstream iss(oss.str());
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(iss, line)) {
        lines.push_back(line);
    }
    std::sort(lines.begin(), lines.end());

    // Create expected output lines and sort them
    std::vector<std::string> expectedLines = {
        "2, 2, 2, 1, 1, 1, sea",
        "4, 4, 4, 2, 2, 2, WA"
    };
    std::sort(expectedLines.begin(), expectedLines.end());

    // Verify the output contains both Cuboids
    BOOST_CHECK_EQUAL_COLLECTIONS(lines.begin(), lines.end(), expectedLines.begin(), expectedLines.end());
}
