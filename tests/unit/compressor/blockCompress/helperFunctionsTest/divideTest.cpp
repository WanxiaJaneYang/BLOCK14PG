#define TESTING
#include "../../../../../src/compressor/Compressor.h"
#include "../../../../../src/compressor/BlockCompress.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include "unitTestHelpers.h"

TEST(divideTest,BASE_CASE_1){
    //arrange
    std::set<CuboidKey> nonOverlappedCuboids;
    std::set<CuboidKey> dividedCuboids;
    std::set<CuboidKey> expectedDividedCuboids;
    CuboidKey cuboidBeingDivided = CuboidKey{'t', Point(0,0), Point(3,2)};
    nonOverlappedCuboids.insert(CuboidKey{'t', Point(1,1), Point(2,1)});
    nonOverlappedCuboids.insert(CuboidKey{'t', Point(0,2), Point(3,2)});
    nonOverlappedCuboids.insert(CuboidKey{'t', Point(0,0), Point(3,0)});
    nonOverlappedCuboids.insert(CuboidKey{'t', Point(0,1), Point(0,1)});
    nonOverlappedCuboids.insert(CuboidKey{'t', Point(3,1), Point(3,1)});

    expectedDividedCuboids.insert(CuboidKey{'t', Point(1,1), Point(2,1)});
    expectedDividedCuboids.insert(CuboidKey{'t', Point(0,2), Point(3,2)});
    expectedDividedCuboids.insert(CuboidKey{'t', Point(0,0), Point(3,0)});
    expectedDividedCuboids.insert(CuboidKey{'t', Point(0,1), Point(0,1)});
    expectedDividedCuboids.insert(CuboidKey{'t', Point(3,1), Point(3,1)});

    //act
    divide(nonOverlappedCuboids,cuboidBeingDivided,dividedCuboids);

    //assert
    EXPECT_EQ(dividedCuboids, expectedDividedCuboids);
    std::cout << "Divided Cuboids:" << std::endl;
    for (auto cuboidKey:dividedCuboids){
        std::cout << cuboidKeyToString(cuboidKey) << std::endl;
    }

}