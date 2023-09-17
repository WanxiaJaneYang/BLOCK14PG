#define TESTING
#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <deque>
#include "unitTestHelpers.h"

TEST(AContainsBTest, BaseCase1)
{
    // case explained
    // cuboid1 in z=1
    // tt
    // tt

    // cuboid2 in z=2
    //   oo
    //   oo

    // expected 1 contains 2
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(1, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(2, 0), Point(3, 1)};
    bool expected = false;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(AContainsBTest, BaseCase2)
{
    // case explained
    // cuboid1 in z=0
    // ttt
    // ttt

    // cuboid2 in z=1
    //  tt
    //  tt

    // expected 1 contains 2
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(2, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'t', Point(1, 0), Point(2, 1)};

    bool expected = true;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(AContainsBTest, BaseCase3)
{
    // case explained
    // cuboid1 in z=0
    // ttt
    // ttt

    // cuboid2 in z=1
    //  oo
    //  oo

    // expected 1 contains 2
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(2, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(1, 0), Point(2, 1)};

    bool expected = false;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(AContainsBTest, BaseCase4)
{
    // case explained
    // cuboid1 in z=0
    // ttt
    // ttt

    // cuboid2 in z=1
    //  t
    //  t

    // expected 1 contains 2
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(2, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'t', Point(1, 0), Point(1, 1)};

    bool expected = true;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(AContainsBTest, BaseCase5)
{
    // case explained
    // cuboid1 in z=0
    // ttt
    // ttt

    // cuboid2 in z=1
    //  ttt
    //  ttt

    // expected 1 contains 2
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(2, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'t', Point(1, 0), Point(3, 1)};

    bool expected = false;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(AContainsBTest, BaseCase6)
{
    // case explained
    // cuboid1 in z=0
    // ttt
    // ttt

    // cuboid2 in z=1
    // tttt

    // expected 1 contains 2
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 0), Point(2, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'t', Point(0, 0), Point(3, 0)};

    bool expected = false;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(AContainsBTest, BaseCase7)
{
    // case explained
    // cuboid1 in z=0
    //  ttt
    //  ttt

    // cuboid2 in z=1
    // ttt

    // expected 1 contains 2
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(1, 0), Point(3, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'t', Point(0, 0), Point(2, 0)};

    bool expected = false;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(AContainsBTest, BaseCase8)
{
    // case explained
    // cuboid1 in z=0
    //  ttt
    //  ttt

    // cuboid2 in z=1
    //  ttt

    // expected 1 contains 2
    // true

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(1, 0), Point(3, 1)};
    CuboidKey cuboidKey2 = CuboidKey{'t', Point(1, 0), Point(3, 0)};

    bool expected = true;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}

TEST(AContainsBTest, BaseCase9)
{
    // case explained
    // cuboid1 in z=0
    //
    //  ttt
    //  ttt

    // cuboid2 in z=1
    //  ttt
    //  ttt

    // expected 1 contains 2
    // false

    // Arrange
    CuboidKey cuboidKey1 = CuboidKey{'t', Point(0, 1), Point(2, 2)};
    CuboidKey cuboidKey2 = CuboidKey{'t', Point(0, 0), Point(2, 1)};

    bool expected = false;

    // act
    bool actual = isAContainsB(cuboidKey1, cuboidKey2);

    // assert
    EXPECT_EQ(expected, actual);
}