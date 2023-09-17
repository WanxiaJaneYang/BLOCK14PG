#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <deque>
#include "unitTestHelpers.h"
#define TESTING
TEST(FindAllMatched, BasicTest)
{
    // explain the test case

    // remainingCuboid: only upper exists
    // upper
    // aaaaa

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ccccccc

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'C', Point(0, 1), Point(6, 1)}] = Cuboid(0, 0, 0, 0, 1, 1, 7, 1, 1, 'C');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, BasicTest2)
{
    // explain the test case

    // remainingCuboid: only lower exists
    // lower
    //
    // ccccccc

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ccccccc

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 1, 0, 7, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'C', Point(0, 1), Point(6, 1)}] = Cuboid(0, 0, 0, 0, 1, 1, 7, 1, 1, 'C');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, BasicTest3)
{
    // explain the test case
    // remainingCuboid: only left exists
    //
    // ee
    // ee

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'E');
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, BasicTest4)
{
    // explain the test case
    // remainingCuboid: only right exists
    //
    //     ff
    //     ff

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 2, 1, 'F');
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, BaseCaseNotFound1)
{
    // explain the test case
    // remainingCuboid: only upper exists
    // upper
    // aaaaa

    // nextPlane
    // cuboid1
    // aaaaaa
    // cuboid2
    //       b
    // cuboid3
    //
    // ccccccc

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(5, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 6, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(6, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 6, 0, 1, 1, 1, 1, 'B');
    nextPlane[CuboidKey{'C', Point(0, 1), Point(6, 1)}] = Cuboid(0, 0, 0, 0, 1, 1, 7, 1, 1, 'C');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}

TEST(FindAllMatched, BaseCaseNotFound2)
{
    // explain the test case
    // remainingCuboid: only lower exists
    // lower
    //
    // ccccccc

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // cccccc

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 1, 0, 7, 0, 0, 'C');

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'C', Point(0, 1), Point(5, 1)}] = Cuboid(0, 0, 0, 0, 1, 1, 6, 1, 1, 'C');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}

TEST(FindAllMatched, BaseCaseNotFound3)
{
    // explain the test case
    // remainingCuboid: only left exists
    //
    // ee

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 1, 1, 'E');
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 2, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}

TEST(FindAllMatched, TwoCuboidsTest1)
{
    // explain the test case
    // remainingCuboid: only upper and lower exists
    // upper
    // aaaaa
    // lower
    //
    // ccccccc

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ccccccc

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 1, 0, 7, 1, 1, 'C');

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'C', Point(0, 1), Point(6, 1)}] = Cuboid(0, 0, 0, 0, 1, 1, 7, 1, 1, 'C');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, TwoCuboidsTest2)
{
    // explain the test case
    // remainingCuboid: only upper and left exists
    // upper
    // aaaaa
    // left
    //
    // ee
    // ee

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'E');
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, TwoCuboidsTest3)
{
    // explain the test case
    // remainingCuboid: only the upper and the right exist
    // upper
    // aaaaa
    // right
    //
    //      ff
    //      ff

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 2, 1, 'F');
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, TwoCuboidsTest4)
{
    // explain the test case
    // remainingCuboid: both left and right exist
    // left
    //
    // ee
    // ee

    // right
    //
    //      ff
    //      ff

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'E');
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 2, 1, 'F');
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, TwoCuboidsTestNotFound1)
{
    // explain the test case
    // remainingCuboid: both left and right exist
    // left
    //
    // ee
    // ee

    // right
    //
    //      ff

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'E');
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 1, 1, 'F');
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}

TEST(FindAllMatched, TwoCuboidsTestNotFound2)
{
    // explain the test case
    // remainingCuboid: only the upper and the right exist
    // upper
    // aaaaa
    // right
    //
    //      ff
    //      ff

    // nextPlane
    // cuboid1
    // aaaaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 2, 1, 'F');
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 7, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}

TEST(FindAllMatched, TwoCuboidsTestNotFound3)
{
    // explain the test case
    // remainingCuboid: only upper and lower exists
    // upper
    // aaaaa
    // lower
    //
    // ccccc

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ccccccc

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 1, 0, 5, 1, 1, 'C');

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'C', Point(0, 1), Point(6, 1)}] = Cuboid(0, 0, 0, 0, 1, 1, 7, 1, 1, 'C');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}

TEST(FindAllMatched, TwoCuboidsTestNotFound4)
{
    // explain the test case
    // remainingCuboid: only upper and left exists
    // upper
    // aaaaa
    // left
    //
    // ee
    // ee

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'E');
    remainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 1)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 1, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}

TEST(FindAllMatched, ThreeCuboidsTest1)
{
    // explain the test case
    // remainingCuboid: uppere, left and right exist
    // upper
    // aaaaa

    // left
    //
    // ee
    // ee

    // right
    //
    //      ff
    //      ff

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'E');
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 2, 1, 'F');
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, ThreeCuboidsNotFoundTest1)
{
    // explain the test case
    // remainingCuboid: uppere, left and right exist
    // upper
    // aaaaaaa

    // left
    //
    // ee
    // ee

    // right
    //
    //      ff
    //      ff

    // nextPlane
    // cuboid1
    // aaaaa
    // cuboid2
    //      bb
    // cuboid3
    //
    // ee
    // ee
    // cuboid4
    //
    //      ff
    //      ff

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 7, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'E');
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 2, 1, 'F');
    remainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(4, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 5, 1, 1, 'A');
    nextPlane[CuboidKey{'B', Point(5, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 5, 0, 1, 2, 1, 1, 'B');
    nextPlane[CuboidKey{'E', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'E');
    nextPlane[CuboidKey{'F', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 1, 1, 'F');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}

TEST(FindAllMatched, FourCuboidsTest1)
{
    // explain the test case
    // remainingCuboid: uppere, left and right and lower exist
    // upper
    // aaaaaaa
    // left
    //
    // aa
    // aa
    // right
    //
    //      aa
    //      aa
    // lower
    //
    //
    //   aaa

    // nextPlane
    // cuboid1
    // aaaaaaa
    // cuboid2
    //
    // aa
    // aa
    // cuboid3
    //
    //      aa
    //      aa
    // cuboid4
    //
    //
    //   aaa

    // expected result
    // true

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 7, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'A');
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 2, 1, 'A');
    remainingCuboid.lower = Cuboid(0, 0, 0, 2, 2, 0, 3, 1, 1, 'A');

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 7, 1, 1, 'A');
    nextPlane[CuboidKey{'A', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'A');
    nextPlane[CuboidKey{'A', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 2, 1, 'A');
    nextPlane[CuboidKey{'A', Point(2, 2), Point(4, 2)}] = Cuboid(0, 0, 0, 2, 2, 1, 3, 1, 1, 'A');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_TRUE(actualResult);
}

TEST(FindAllMatched, FourCuboidsTestNotFound1)
{
    // explain the test case
    // remainingCuboid: uppere, left and right and lower exist
    // upper
    // aaaaaaa
    // left
    //
    // aa
    // aa
    // right
    //
    //      aa
    //      aa
    // lower
    //
    //
    //   aaa

    // nextPlane
    // cuboid1
    // aaaaaaa
    // cuboid2
    //
    // aa
    // aa
    // cuboid3
    //
    //      aa
    //      aa
    // cuboid4
    //
    //
    //   aaa
    //   aaa

    // expected result
    // false

    // Arrange
    RemainingCuboid remainingCuboid;
    remainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 7, 1, 1, 'A');
    remainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 2, 2, 1, 'A');
    remainingCuboid.right = Cuboid(0, 0, 0, 5, 1, 0, 2, 2, 1, 'A');
    remainingCuboid.lower = Cuboid(0, 0, 0, 2, 2, 0, 3, 1, 1, 'A');

    std::map<CuboidKey, Cuboid> nextPlane;
    nextPlane[CuboidKey{'A', Point(0, 0), Point(6, 0)}] = Cuboid(0, 0, 0, 0, 0, 1, 7, 1, 1, 'A');
    nextPlane[CuboidKey{'A', Point(0, 1), Point(1, 2)}] = Cuboid(0, 0, 0, 0, 1, 1, 2, 2, 1, 'A');
    nextPlane[CuboidKey{'A', Point(5, 1), Point(6, 2)}] = Cuboid(0, 0, 0, 5, 1, 1, 2, 2, 1, 'A');
    nextPlane[CuboidKey{'A', Point(2, 2), Point(4, 3)}] = Cuboid(0, 0, 0, 2, 2, 1, 3, 1, 1, 'A');

    // Act
    bool actualResult = findAllMatched(remainingCuboid, nextPlane);

    // Assert
    EXPECT_FALSE(actualResult);
}
