#define TESTING
#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include "unitTestHelpers.h"

TEST(retrieveTest,BASE_CASE_1){
    //ARRANGE
    std::map<CuboidKey, Cuboid> cuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromNextPlane;
    cuboidsFromPrevPlane[CuboidKey{'t', Point(1,1), Point(2,1)}] = Cuboid(0,0,0,1,1,0,2,1,1,'t');
    cuboidsFromPrevPlane[CuboidKey{'t', Point(0,2), Point(3,2)}] = Cuboid(0,0,0,0,2,0,4,1,1,'t');

    cuboidsFromNextPlane[CuboidKey{'t', Point(0,0), Point(3,0)}] = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(0,1), Point(0,1)}] = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(3,1), Point(3,1)}] = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(0,2), Point(3,2)}] = Cuboid(0,0,0,0,2,2,4,1,1,'t');
    std::set<CuboidKey> uniqueCuboids;
    std::set<CuboidKey> nonOverlappedCuboids;

    //ACT
    retrieveUniqueAndNonOverlapping(cuboidsFromPrevPlane,cuboidsFromNextPlane,uniqueCuboids,nonOverlappedCuboids);
    EXPECT_EQ(uniqueCuboids.size(), 5);

    //ASSERT
    std::set<CuboidKey> expectedUniqueCuboids;
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(1,1), Point(2,1)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,2), Point(3,2)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,0), Point(3,0)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,1), Point(0,1)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(3,1), Point(3,1)});

    EXPECT_EQ(uniqueCuboids, expectedUniqueCuboids);
    std::cout << "Non overlapping Cuboids:" << std::endl;
    for (auto cuboidKey:nonOverlappedCuboids){
        std::cout << cuboidKeyToString(cuboidKey) << std::endl;
    }
    EXPECT_EQ(nonOverlappedCuboids, expectedUniqueCuboids);

}

TEST(retrieveTest,BASE_CASE_2){
    //ARRANGE
    //prev plane
    //
    // tt
    // tt

    //next plane
    //tttt
    //t  t
    //tttt

    std::map<CuboidKey, Cuboid> cuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromNextPlane;
    cuboidsFromPrevPlane[CuboidKey{'t', Point(1,1), Point(2,2)}] = Cuboid(0,0,0,1,1,0,2,2,1,'t');
    
    cuboidsFromNextPlane[CuboidKey{'t', Point(0,0), Point(3,0)}] = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(0,1), Point(0,1)}] = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(3,1), Point(3,1)}] = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(0,2), Point(3,2)}] = Cuboid(0,0,0,0,2,2,4,1,1,'t');
    std::set<CuboidKey> uniqueCuboids;
    std::set<CuboidKey> nonOverlappedCuboids;

    //ACT
    retrieveUniqueAndNonOverlapping(cuboidsFromPrevPlane,cuboidsFromNextPlane,uniqueCuboids,nonOverlappedCuboids);
    EXPECT_EQ(uniqueCuboids.size(), 5);

    //ASSERT
    std::set<CuboidKey> expectedUniqueCuboids;
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(1,1), Point(2,2)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,2), Point(3,2)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,0), Point(3,0)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,1), Point(0,1)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(3,1), Point(3,1)});


    std::set<CuboidKey> expectedNonOverlappedCuboids;
    expectedNonOverlappedCuboids.insert(CuboidKey{'t', Point(1,1), Point(2,2)});
    expectedNonOverlappedCuboids.insert(CuboidKey{'t', Point(0,0), Point(3,0)});
    expectedNonOverlappedCuboids.insert(CuboidKey{'t', Point(0,1), Point(0,1)});
    expectedNonOverlappedCuboids.insert(CuboidKey{'t', Point(3,1), Point(3,1)});

    EXPECT_EQ(uniqueCuboids, expectedUniqueCuboids);
    std::cout << "Non overlapping Cuboids:" << std::endl;
    for (auto cuboidKey:nonOverlappedCuboids){
        std::cout << cuboidKeyToString(cuboidKey) << std::endl;
    }
    EXPECT_EQ(nonOverlappedCuboids, expectedNonOverlappedCuboids);

}

TEST(retrieveTest,BASE_CASE_3){
    //ARRANGE
    std::map<CuboidKey, Cuboid> cuboidsFromPrevPlane;
    std::map<CuboidKey, Cuboid> cuboidsFromNextPlane;
    cuboidsFromPrevPlane[CuboidKey{'t', Point(1,1), Point(2,1)}] = Cuboid(0,0,0,1,1,0,2,1,1,'t');

    cuboidsFromNextPlane[CuboidKey{'t', Point(0,0), Point(3,0)}] = Cuboid(0,0,0,0,0,2,4,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(0,1), Point(0,1)}] = Cuboid(0,0,0,0,1,2,1,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(3,1), Point(3,1)}] = Cuboid(0,0,0,3,1,2,1,1,1,'t');
    cuboidsFromNextPlane[CuboidKey{'t', Point(0,2), Point(3,2)}] = Cuboid(0,0,0,0,2,2,4,1,1,'t');
    std::set<CuboidKey> uniqueCuboids;
    std::set<CuboidKey> nonOverlappedCuboids;

    //ACT
    retrieveUniqueAndNonOverlapping(cuboidsFromPrevPlane,cuboidsFromNextPlane,uniqueCuboids,nonOverlappedCuboids);
    EXPECT_EQ(uniqueCuboids.size(), 5);

    //ASSERT
    std::set<CuboidKey> expectedUniqueCuboids;
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(1,1), Point(2,1)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,2), Point(3,2)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,0), Point(3,0)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(0,1), Point(0,1)});
    expectedUniqueCuboids.insert(CuboidKey{'t', Point(3,1), Point(3,1)});

    EXPECT_EQ(uniqueCuboids, expectedUniqueCuboids);
    EXPECT_EQ(nonOverlappedCuboids, expectedUniqueCuboids);

}