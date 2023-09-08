#ifndef PLANE_COMPRESS_TEST_H
#define PLANE_COMPRESS_TEST_H

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <filesystem>
#include "../../../src/compressor/Compressor.h"
#include "../../../src/globals/globals.h"

std::vector<std::string> listInputFiles(const std::string &directory);
std::deque<std::deque<std::deque<Cuboid>>> convertFileContentToLines(const std::string &fileContent);
std::string writeContentOfCuboid(const Cuboid &cuboid);
std::string writeReadContent(const std::deque<std::deque<Cuboid>> &planes);

#endif
