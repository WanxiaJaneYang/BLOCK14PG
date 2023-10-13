#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <deque>
#include "unitTestHelpers.h"

TEST(MinusCuboidTest, BaseCase)
{
    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'A');
    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper));
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left));
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right));
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower));
}

TEST(MinusCuboidTest, DifferentColor)
{
    // it should throw an error if the colors are different

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 0, 0, 0, 1, 1, 1, 'B');

    // Act
    try
    {
        minusCuboid(currentCuboid, prevCuboid);
        FAIL() << "Expected std::runtime_error";
    }
    catch (std::runtime_error const &err)
    {
        EXPECT_EQ(err.what(), std::string("Error: the two cuboids are not in the same tag"));
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(MinusCuboidTest, LeftMinus)
{
    // explain the test case
    // current
    // aa
    // aa

    // prev
    // a
    // a

    // expected: only the right side of the current cuboid is left
    //  a
    //  a

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 2, 2, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 0, 0, 0, 1, 2, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 1, 0, 0, 1, 2, 1, 'A');
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper));
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left));
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right));
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower));
}

TEST(MinusCuboidTest, RightMinus)
{
    // explain the test case
    // current
    // aaa
    // aaa
    // aaa

    // prev
    //  aa
    //  aa
    //  aa

    // expected: only the left side of the current cuboid is left
    // a
    // a
    // a

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 3, 3, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 1, 0, 0, 2, 3, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 1, 3, 1, 'A');
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;

    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;

    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;

    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, UpperMinus)
{
    // explain the test case
    // current
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa

    // prev
    // aaaaa
    // aaaaa
    // aaaaa

    // expected: only the lower side of the current cuboid is left
    //
    //
    //
    // aaaaa

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 5, 4, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 0, 0, 0, 5, 3, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 3, 0, 5, 1, 1, 'A');

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, LowerMinus)
{
    // explain the test case
    // current
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa

    // prev
    //
    //
    // aaaaa
    // aaaaa

    // expected: only the upper side of the current cuboid is left
    // aaaaa
    // aaaaa
    //
    //

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 5, 4, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 0, 2, 0, 5, 2, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 2, 1, 'A');
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, MilldeMinus)
{
    // explain the test case
    // current
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa

    // prev
    //  aa
    //  aa
    //  aa
    //  aa

    // expected: only the left side and the right side of the current cuboid are left
    // left
    // a
    // a
    // a
    // a
    // right
    //    aa
    //    aa
    //    aa
    //    aa

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 5, 4, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 1, 0, 0, 2, 4, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 1, 4, 1, 'A');
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 3, 0, 0, 2, 4, 1, 'A');
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, MiddleMinus2)
{
    // explain the test case
    // current
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa

    // prev
    //
    // aaaaa
    // aaaaa
    //
    //

    // expected: only the upper side and the lower side of the current cuboid are left
    // upper
    // aaaaa
    //
    // lower
    //
    //
    //
    // aaaaa
    // aaaaa

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 5, 5, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 0, 1, 0, 5, 2, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 1, 1, 'A');
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 3, 0, 5, 2, 1, 'A');

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, RightLowerCornerMinus)
{
    // explain the test case
    // current
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa

    // prev
    //
    //
    //  aaa
    //  aaa
    //  aaa

    // expected: only the upper side and the left side of the current cuboid are left
    // upper
    // aaaaa
    // aaaaa

    // left
    //
    //
    // aa
    // aa
    // aa

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 5, 5, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 2, 2, 0, 3, 3, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 2, 1, 'A');
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 2, 0, 2, 3, 1, 'A');
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, LeftUpperCornerMinus)
{
    // explain the test case
    // current
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa

    // prev
    // aaa
    // aaa
    // aaa
    //
    //

    // expected: only the right side and the lower side of the current cuboid are left
    // right
    //    aa
    //    aa
    //    aa
    //    aa
    //    aa

    // lower
    //
    //
    //
    // aaa
    // aaa

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 5, 5, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 0, 0, 0, 3, 3, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 3, 0, 0, 2, 5, 1, 'A');
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 3, 0, 3, 2, 1, 'A');

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, RightUpperCornerMinus)
{
    // explain the test case
    // current
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa

    // prev
    //   aaa
    //   aaa

    // expected: only the left side and the lower side of the current cuboid are left
    // left
    // aa
    // aa
    // aa
    // aa
    // aa

    // lower
    //
    //
    //   aaa
    //   aaa
    //   aaa

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 5, 5, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 2, 0, 0, 3, 2, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 2, 5, 1, 'A');
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 2, 2, 0, 3, 3, 1, 'A');

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, MinusLeftLower)
{
    // explain the test case
    // current
    // aaaaa
    // aaaaa
    // aaaaa
    // aaaaa

    // prev
    //
    //
    //
    // aa
    // aa

    // expected: only the upper side and the right side of the current cuboid are left
    // upper
    // aaaaa
    // aaaaa
    // aaaaa

    // right
    //
    //
    //
    //  aaa
    //  aaa

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 5, 5, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 0, 3, 0, 2, 2, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 5, 3, 1, 'A');
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 2, 3, 0, 3, 2, 1, 'A');
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 0, 0, 0, 0, 0, 0, -1);

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}

TEST(MinusCuboidTest, MinusCenter)
{
    // explain the test case
    // current
    // aaaaaaa
    // aaaaaaa
    // aaaaaaa
    // aaaaaaa
    // aaaaaaa

    // prev
    //
    //  aaa
    //  aaa
    //
    //

    // expected: upper, left, right, lower are left
    // upper
    // aaaaaaa

    // left
    //
    // a
    // a
    // a
    // a

    // right
    //
    //     aaa
    //     aaa
    //     aaa
    //     aaa

    // lower
    //
    //
    //
    //  aaa
    //  aaa

    // Arrange
    Cuboid currentCuboid(0, 0, 0, 0, 0, 0, 7, 5, 1, 'A');
    Cuboid prevCuboid(0, 0, 0, 1, 1, 0, 3, 2, 1, 'A');

    RemainingCuboid expectedRemainingCuboid;
    expectedRemainingCuboid.upper = Cuboid(0, 0, 0, 0, 0, 0, 7, 1, 1, 'A');
    expectedRemainingCuboid.left = Cuboid(0, 0, 0, 0, 1, 0, 1, 4, 1, 'A');
    expectedRemainingCuboid.right = Cuboid(0, 0, 0, 4, 1, 0, 3, 4, 1, 'A');
    expectedRemainingCuboid.lower = Cuboid(0, 0, 0, 1, 3, 0, 3, 2, 1, 'A');

    // Act
    RemainingCuboid actualRemainingCuboid = minusCuboid(currentCuboid, prevCuboid);

    // Assert
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.upper, actualRemainingCuboid.upper)) << "upper cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.upper) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.upper) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.left, actualRemainingCuboid.left)) << "left cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.left) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.left) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.right, actualRemainingCuboid.right)) << "right cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.right) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.right) << std::endl;
    EXPECT_TRUE(areCuboidsEqual(expectedRemainingCuboid.lower, actualRemainingCuboid.lower)) << "lower cuboid is not equal, expected cuboid: " << cuboidToString(expectedRemainingCuboid.lower) << "actual cuboid: " << cuboidToString(actualRemainingCuboid.lower) << std::endl;
}