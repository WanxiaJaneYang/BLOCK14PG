#include "../helperFunctionsTest/unitTestHelpers.h"
#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <deque>

TEST(BlockCompressTest, BaseCase1)
{
    // case explained
    // too
    // oot

    // too
    // oot

    std::deque<std::deque<Cuboid>> planes;
    std::deque<Cuboid> plane1;
    std::deque<Cuboid> plane2;
    plane1.push_back(Cuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 't'));
    plane1.push_back(Cuboid(0, 0, 0, 1, 0, 0, 2, 1, 1, 'o'));
    plane1.push_back(Cuboid(0, 0, 0, 0, 1, 0, 2, 1, 1, 'o'));
    plane1.push_back(Cuboid(0, 0, 0, 1, 1, 0, 1, 1, 1, 't'));

    planes.push_back(plane1);

    plane2.push_back(Cuboid(0, 0, 0, 0, 0, 1, 1, 1, 1, 't'));
    plane2.push_back(Cuboid(0, 0, 0, 1, 0, 1, 2, 1, 1, 'o'));
    plane2.push_back(Cuboid(0, 0, 0, 0, 1, 1, 2, 1, 1, 'o'));
    plane2.push_back(Cuboid(0, 0, 0, 2, 1, 1, 1, 1, 1, 't'));

    planes.push_back(plane2);

    std::cout << "planes size: " << planes.size() << std::endl;
    std::cout << "plane1 size: " << plane1.size() << std::endl;
    std::cout << "plane2 size: " << plane2.size() << std::endl;

    blockCompress(planes);

    // expected in the output tasks
    Cuboid cuboid1 = Cuboid(0, 0, 0, 0, 0, 0, 1, 1, 2, 't');
    Cuboid cuboid2 = Cuboid(0, 0, 0, 1, 0, 0, 2, 1, 2, 'o');
    Cuboid cuboid3 = Cuboid(0, 0, 0, 0, 1, 0, 2, 1, 2, 'o');
    Cuboid cuboid4 = Cuboid(0, 0, 0, 1, 1, 0, 1, 1, 2, 't');

    // check the output tasks
    EXPECT_EQ(GlobalVars::outputTasks.size(), 4);
    Cuboid output1;
    Cuboid output2;
    Cuboid output3;
    Cuboid output4;
    GlobalVars::outputTasks.pop(output1);
    EXPECT_TRUE(areCuboidsEqual(output1, cuboid1));
    GlobalVars::outputTasks.pop(output2);
    EXPECT_TRUE(areCuboidsEqual(output2, cuboid2));
    GlobalVars::outputTasks.pop(output3);
    EXPECT_TRUE(areCuboidsEqual(output3, cuboid3));
    GlobalVars::outputTasks.pop(output4);
    EXPECT_TRUE(areCuboidsEqual(output4, cuboid4));

    // print all the output tasks
    std::cout << "output1: " << cuboidToString(output1) << std::endl;
    std::cout << "output2: " << cuboidToString(output2) << std::endl;
    std::cout << "output3: " << cuboidToString(output3) << std::endl;
    std::cout << "output4: " << cuboidToString(output4) << std::endl;

    Cuboid cuboid;
    int count = 5;
    while (!GlobalVars::outputTasks.size() != 0)
    {
        GlobalVars::outputTasks.pop(cuboid);
        std::cout << "output: " << count << " " << cuboidToString(cuboid) << std::endl;
        count++;
    }
}