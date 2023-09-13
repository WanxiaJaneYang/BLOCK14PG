#ifndef UNIT_TEST_HELPERS_H
#define UNIT_TEST_HELPERS_H

#include <map>
#include "../../../../../src/compressor/Compressor.h"

bool areMapsEqual(const std::map<CuboidKey, Cuboid> &expected, const std::map<CuboidKey, Cuboid> &actual);
bool areCuboidsEqual(const Cuboid &expected, const Cuboid &actual);

#endif