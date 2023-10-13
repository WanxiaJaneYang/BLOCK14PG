#define TESTING
#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include "unitTestHelpers.h"

TEST(cuboidsSameAreaTest,VALID_TEST1){
    //case
    //plane1:
    // oooo
    // otto
    // oooo

    //plane2:
    // tttt
    // tttt
    // tttt

    //plane3:
    // tttt
    // toot
    // tttt

    // Arrange
    std::map<CuboidKey, Cuboid> prevPlane;
    std::map<CuboidKey, Cuboid> nextPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromNextPlane;
    CuboidKey middleCuboid= CuboidKey{'t', Point(0,0), Point(3,2)};
    //prevPlane cuboids
    CuboidKey cuboidKey1 = CuboidKey{'o', Point(0,0), Point(3,0)};
    Cuboid cuboid1 = Cuboid(0,0,0,0,0,0,4,1,1,'o');
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0,1), Point(0,1)};
    Cuboid cuboid2 = Cuboid(0,0,0,0,1,0,1,1,1,'o');
    CuboidKey cuboidKey3 = CuboidKey{'t', Point(1,1), Point(1,2)};
    Cuboid cuboid3 = Cuboid(0,0,0,1,1,0,2,1,1,'t');
    CuboidKey cuboidKey4 = CuboidKey{'o', Point(3,1), Point(3,1)};
    Cuboid cuboid4 = Cuboid(0,0,0,3,1,0,1,1,1,'o');
    CuboidKey cuboidKey5 = CuboidKey{'o', Point(0,2), Point(3,2)};
    Cuboid cuboid5 = Cuboid(0,0,0,0,2,0,4,1,1,'o');
    //nextPlane cuboids
    CuboidKey cuboidKey6 = CuboidKey{'t', Point(0,0), Point(3,0)};
    Cuboid cuboid6 = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    CuboidKey cuboidKey7 = CuboidKey{'t', Point(0,1), Point(0,1)};
    Cuboid cuboid7 = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    CuboidKey cuboidKey8 = CuboidKey{'o', Point(1,1), Point(1,2)};
    Cuboid cuboid8 = Cuboid(0,0,0,1,1,2,2,1,1,'o');
    CuboidKey cuboidKey9 = CuboidKey{'t', Point(3,1), Point(3,1)};
    Cuboid cuboid9 = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    CuboidKey cuboidKey10 = CuboidKey{'t', Point(0,2), Point(3,2)};
    Cuboid cuboid10 = Cuboid(0,0,0,0,2,2,4,1,1,'t');

    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey1, cuboid1));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey2, cuboid2));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey3, cuboid3));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey4, cuboid4));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey5, cuboid5));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey6, cuboid6));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey7, cuboid7));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey8, cuboid8));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey9, cuboid9));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey10, cuboid10));
    //act
    CuboidsInSameArea(prevPlane, cuboidsFromPrevPlane, nextPlane, cuboidsFromNextPlane, middleCuboid);
    //expected
    std::map<CuboidKey, Cuboid> expectedCuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> expectedCuboidsFromNextPlane;
    expectedCuboidsFromPrevPlane[CuboidKey{'t', Point(1,1), Point(1,2)}] = Cuboid(0,0,0,1,1,0,2,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,0), Point(3,0)}] = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,1), Point(0,1)}] = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(3,1), Point(3,1)}] = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,2), Point(3,2)}] = Cuboid(0,0,0,0,2,2,4,1,1,'t');
    //assert
    EXPECT_TRUE(areMapsEqual(expectedCuboidsFromPrevPlane, cuboidsFromPrevPlane));
    EXPECT_TRUE(areMapsEqual(expectedCuboidsFromNextPlane, cuboidsFromNextPlane));
}

TEST(cuboidsSameAreaTest,VALID_TEST2){
    //case
    //plane1:
    // oooott
    // ottott
    // oooott

    //plane2:
    // tttt
    // tttt
    // tttt

    //plane3:
    // ttttoo
    // tootoo
    // ttttoo

    // Arrange
    std::map<CuboidKey, Cuboid> prevPlane;
    std::map<CuboidKey, Cuboid> nextPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromNextPlane;
    CuboidKey middleCuboid= CuboidKey{'t', Point(0,0), Point(3,2)};
    //prevPlane cuboids
    CuboidKey cuboidKey1 = CuboidKey{'o', Point(0,0), Point(3,0)};
    Cuboid cuboid1 = Cuboid(0,0,0,0,0,0,4,1,1,'o');
    CuboidKey cuboidKey11 = CuboidKey{'t', Point(5,0), Point(6,2)};
    Cuboid cuboid11 = Cuboid(0,0,0,5,0,0,2,3,1,'t');
    CuboidKey cuboidKey2 = CuboidKey{'o', Point(0,1), Point(0,1)};
    Cuboid cuboid2 = Cuboid(0,0,0,0,1,0,1,1,1,'o');
    CuboidKey cuboidKey3 = CuboidKey{'t', Point(1,1), Point(1,2)};
    Cuboid cuboid3 = Cuboid(0,0,0,1,1,0,2,1,1,'t');
    CuboidKey cuboidKey4 = CuboidKey{'o', Point(3,1), Point(3,1)};
    Cuboid cuboid4 = Cuboid(0,0,0,3,1,0,1,1,1,'o');
    CuboidKey cuboidKey5 = CuboidKey{'o', Point(0,2), Point(3,2)};
    Cuboid cuboid5 = Cuboid(0,0,0,0,2,0,4,1,1,'o');
    //nextPlane cuboids
    CuboidKey cuboidKey6 = CuboidKey{'t', Point(0,0), Point(3,0)};
    Cuboid cuboid6 = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    CuboidKey cuboidKey7 = CuboidKey{'t', Point(0,1), Point(0,1)};
    Cuboid cuboid7 = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    CuboidKey cuboidKey8 = CuboidKey{'o', Point(1,1), Point(1,2)};
    Cuboid cuboid8 = Cuboid(0,0,0,1,1,2,2,1,1,'o');
    CuboidKey cuboidKey9 = CuboidKey{'t', Point(3,1), Point(3,1)};
    Cuboid cuboid9 = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    CuboidKey cuboidKey10 = CuboidKey{'t', Point(0,2), Point(3,2)};
    Cuboid cuboid10 = Cuboid(0,0,0,0,2,2,4,1,1,'t');
    CuboidKey cuboidKey12 = CuboidKey{'o', Point(5,0), Point(6,2)};
    Cuboid cuboid12 = Cuboid(0,0,0,5,0,2,2,3,1,'o');

    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey1, cuboid1));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey2, cuboid2));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey3, cuboid3));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey4, cuboid4));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey5, cuboid5));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey6, cuboid6));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey7, cuboid7));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey8, cuboid8));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey9, cuboid9));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey10, cuboid10));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey11, cuboid11));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey12, cuboid12));
    //act
    CuboidsInSameArea(prevPlane, cuboidsFromPrevPlane, nextPlane, cuboidsFromNextPlane, middleCuboid);
    //expected
    std::map<CuboidKey, Cuboid> expectedCuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> expectedCuboidsFromNextPlane;
    expectedCuboidsFromPrevPlane[CuboidKey{'t', Point(1,1), Point(1,2)}] = Cuboid(0,0,0,1,1,0,2,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,0), Point(3,0)}] = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,1), Point(0,1)}] = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(3,1), Point(3,1)}] = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,2), Point(3,2)}] = Cuboid(0,0,0,0,2,2,4,1,1,'t');
    //assert
    EXPECT_TRUE(areMapsEqual(expectedCuboidsFromPrevPlane, cuboidsFromPrevPlane));
    EXPECT_TRUE(areMapsEqual(expectedCuboidsFromNextPlane, cuboidsFromNextPlane));
}

TEST(cuboidsSameAreaTest,VALID_TEST3){
    //case
    //plane1:
    // oooott
    // ottott
    // oooott

    //plane2:
    // tttttt
    // tttttt
    // tttttt

    //plane3:
    // ttttoo
    // tootoo
    // ttttoo

    // Arrange
    std::map<CuboidKey, Cuboid> prevPlane;
    std::map<CuboidKey, Cuboid> nextPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromNextPlane;
    CuboidKey middleCuboid= CuboidKey{'t', Point(0,0), Point(5,2)};
    //prevPlane cuboids
    CuboidKey cuboidKey1 = CuboidKey{'o', Point(0,0), Point(3,0)};
    Cuboid cuboid1 = Cuboid(0,0,0,0,0,0,4,1,1,'o');
    CuboidKey cuboidKey2 = CuboidKey{'t', Point(4,0), Point(5,2)};
    Cuboid cuboid2 = Cuboid(0,0,0,4,0,0,2,3,1,'t');
    CuboidKey cuboidKey3 = CuboidKey{'o', Point(0,1), Point(0,1)};
    Cuboid cuboid3 = Cuboid(0,0,0,0,1,0,1,1,1,'o');
    CuboidKey cuboidKey4 = CuboidKey{'t', Point(1,1), Point(1,2)};
    Cuboid cuboid4 = Cuboid(0,0,0,1,1,0,2,1,1,'t');
    CuboidKey cuboidKey5 = CuboidKey{'o', Point(3,1), Point(3,1)};
    Cuboid cuboid5 = Cuboid(0,0,0,3,1,0,1,1,1,'o');
    CuboidKey cuboidKey6 = CuboidKey{'o', Point(0,2), Point(3,2)};
    Cuboid cuboid6 = Cuboid(0,0,0,0,2,0,4,1,1,'o');
    //nextPlane cuboids
    CuboidKey cuboidKey7 = CuboidKey{'t', Point(0,0), Point(3,0)};
    Cuboid cuboid7 = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    CuboidKey cuboidKey8 = CuboidKey{'t', Point(0,1), Point(0,1)};
    Cuboid cuboid8 = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    CuboidKey cuboidKey9 = CuboidKey{'o', Point(1,1), Point(1,2)};
    Cuboid cuboid9 = Cuboid(0,0,0,1,1,2,2,1,1,'o');
    CuboidKey cuboidKey10 = CuboidKey{'t', Point(3,1), Point(3,1)};
    Cuboid cuboid10 = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    CuboidKey cuboidKey11 = CuboidKey{'t', Point(0,2), Point(3,2)};
    Cuboid cuboid11 = Cuboid(0,0,0,0,2,2,4,1,1,'t');
    CuboidKey cuboidKey12 = CuboidKey{'o', Point(4,0), Point(5,2)};
    Cuboid cuboid12 = Cuboid(0,0,0,4,0,2,2,3,1,'o');

    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey1, cuboid1));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey2, cuboid2));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey3, cuboid3));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey4, cuboid4));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey5, cuboid5));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey6, cuboid6));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey7, cuboid7));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey8, cuboid8));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey9, cuboid9));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey10, cuboid10));
    nextPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey11, cuboid11));
    prevPlane.insert(std::pair<CuboidKey, Cuboid>(cuboidKey12, cuboid12));
    //act
    CuboidsInSameArea(prevPlane, cuboidsFromPrevPlane, nextPlane, cuboidsFromNextPlane, middleCuboid);
    //expected
    std::map<CuboidKey, Cuboid> expectedCuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> expectedCuboidsFromNextPlane;
    expectedCuboidsFromPrevPlane[CuboidKey{'t', Point(1,1), Point(1,2)}] = Cuboid(0,0,0,1,1,0,2,1,1,'t');
    expectedCuboidsFromPrevPlane[CuboidKey{'t', Point(4,0), Point(5,2)}] = Cuboid(0,0,0,4,0,0,2,3,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,0), Point(3,0)}] = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,1), Point(0,1)}] = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(3,1), Point(3,1)}] = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    expectedCuboidsFromNextPlane[CuboidKey{'t', Point(0,2), Point(3,2)}] = Cuboid(0,0,0,0,2,2,4,1,1,'t');
    //assert
    EXPECT_TRUE(areMapsEqual(expectedCuboidsFromPrevPlane, cuboidsFromPrevPlane));
    EXPECT_TRUE(areMapsEqual(expectedCuboidsFromNextPlane, cuboidsFromNextPlane));
}