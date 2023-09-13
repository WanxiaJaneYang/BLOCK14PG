#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <deque>
#include "unitTestHelpers.h"

// Make sure to include the other required headers and definitions...

TEST(TransformToMapTest, BasicTest)
{
    // Arrange
    std::deque<Cuboid> plane;
    plane.push_back(Cuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'A'));
    plane.push_back(Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'B'));

    std::map<CuboidKey, Cuboid> expectedCuboids;
    expectedCuboids[CuboidKey{'A', Point(0, 0), Point(0, 0)}] = Cuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'A');
    expectedCuboids[CuboidKey{'B', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'B');

    std::map<CuboidKey, Cuboid> actualCuboids;

    // Act
    transformToMap(plane, actualCuboids);

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
    transformToMap(plane, actualCuboids);

    // Assert
    EXPECT_TRUE(areMapsEqual(expectedCuboids, actualCuboids));
}

TEST(TransformToMapTest, MoreCuboids)
{
    // Arrange
    std::deque<Cuboid> plane;
    plane.push_back(Cuboid(0, 0, 0, 0, 0, 0, 3, 4, 1, 'A'));
    plane.push_back(Cuboid(0, 0, 0, 3, 0, 0, 4, 4, 1, 'B'));
    plane.push_back(Cuboid(0, 0, 0, 0, 4, 0, 5, 2, 1, 'C'));

    std::map<CuboidKey, Cuboid> expectedCuboids;
    expectedCuboids[CuboidKey{'A', Point(0, 0), Point(2, 3)}] = Cuboid(0, 0, 0, 0, 0, 0, 3, 4, 1, 'A');
    expectedCuboids[CuboidKey{'B', Point(3, 0), Point(6, 3)}] = Cuboid(0, 0, 0, 3, 0, 0, 4, 4, 1, 'B');
    expectedCuboids[CuboidKey{'C', Point(0, 4), Point(4, 5)}] = Cuboid(0, 0, 0, 0, 4, 0, 5, 2, 1, 'C');
    std::map<CuboidKey, Cuboid> actualCuboids;

    // Act
    transformToMap(plane, actualCuboids);

    // Assert
    EXPECT_TRUE(areMapsEqual(expectedCuboids, actualCuboids));
}