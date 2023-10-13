#define TESTING
#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <deque>
#include "unitTestHelpers.h"

TEST(OverlapTest, BaseCase1)
{
    // case explained
    // cuboid1 in z=0
    // tt
    // tt

    // cuboid2 in z=1
    //   oo
    //   oo

    // expected is overlapped
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(1, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(2, 0), Point(3, 1)};
    bool expected = false;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, BaseCase2)
{
    // case explained
    // cuboid1 in z=0
    // tt
    // tt

    // cuboid2 in z=1
    //  oo
    //  oo

    // expected is overlapped
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(1, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(1, 0), Point(2, 1)};
    bool expected = true;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, BaseCase3)
{
    // case explained
    // cuboid1 in z=0
    // tt
    // tt

    // cuboid2 in z=1
    //
    // oo
    // oo

    // expected is overlapped
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(1, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0, 1), Point(1, 2)};
    bool expected = true;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, BaseCase4)
{
    // case explained
    // cuboid1 in z=0
    // tt
    // tt

    // cuboid2 in z=1
    //
    //
    // oo
    // oo

    // expected is overlapped
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(1, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0, 2), Point(1, 3)};
    bool expected = false;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, BaseCase5)
{
    // case explained
    // cuboid1 in z=0
    // tt
    // tt

    // cuboid2 in z=1
    //
    //  oo
    //  oo

    // expected is overlapped
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(1, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(1, 1), Point(2, 2)};
    bool expected = true;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, BaseCase6)
{
    // case explained
    // cuboid1 in z=0
    //  tt
    //  tt

    // cuboid2 in z=1
    // oo
    // oo

    // expected is overlapped
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(1, 0), Point(2, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0, 0), Point(1, 1)};
    bool expected = true;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, BaseCase7)
{
    // case explained
    // cuboid1 in z=0
    //   tt
    //   tt

    // cuboid2 in z=1
    //  oo
    //  oo

    // expected is overlapped
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(2, 0), Point(3, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0, 0), Point(1, 1)};
    bool expected = false;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, BaseCase8)
{
    // case explained
    // cuboid1 in z=0
    //
    //
    // tt
    // tt

    // cuboid2 in z=1
    // oo
    // oo

    // expected is overlapped
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 2), Point(1, 3)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0, 0), Point(1, 1)};
    bool expected = false;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, IntermediaryCase1)
{
    // case explained
    // cuboid1 in z=0
    //  tt
    //  tt

    // cuboid2 in z=1
    // ooo
    // ooo

    // expected is overlapped
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(1, 0), Point(2, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0, 0), Point(2, 1)};

    bool expected = true;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(OverlapTest, IntermediaryCase2)
{
    // case explained
    // cuboid1 in z=0
    //
    //  tt
    //  tt

    // cuboid2 in z=1
    // oooo
    // oooo
    // oooo

    // expected is overlapped
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(1, 1), Point(2, 2)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0, 0), Point(3, 2)};

    bool expected = true;

    // act
    bool actual = isOverLapped(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}