#define TESTING

#include "../../../../../src/compressor/Compressor.h"
#include <gtest/gtest.h>
#include <iostream>
#include "unitTestHelpers.h"

#define TRANSFORM_TO_MAP_TEST_CPP

// Make sure to include the other required headers and definitions...

TEST(TransformToMapTest, BasicTest)
{
    // Arrange
    std::deque<Cuboid> plane = {
        Cuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'A'),
        Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'B'),
    };

    std::map<CuboidKey, Cuboid> expectedCuboids;
    expectedCuboids[CuboidKey{Point(0, 0), Point(1, 1)}] = Cuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'A');
    expectedCuboids[CuboidKey{Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'B');

    std::map<CuboidKey, Cuboid> actualCuboids;

    // Act
    tranformToMap(plane, actualCuboids);

    // Assert
    EXPECT_TRUE(areMapsEqual(expectedCuboids, actualCuboids));
}

TEST(TransformToMapTest, EmptyInput)
{
    // Arrange
    std::deque<Cuboid> plane = {};
    std::map<CuboidKey, Cuboid> expectedCuboids = {};
    std::map<CuboidKey, Cuboid> actualCuboids;

    // Act
    tranformToMap(plane, actualCuboids);

    // Assert
    EXPECT_TRUE(areMapsEqual(expectedCuboids, actualCuboids));
}

// ... Add more tests as needed ...

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
