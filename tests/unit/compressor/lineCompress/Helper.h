#ifndef INPUT_TEST_H
#define INPUT_TEST_H

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include "../../../../src/compressor/Compressor.h"
#include "../../../../src/globals/globals.h"
#include "../../../../src/cores/Block.h"

std::vector<std::string> listInputFiles(const std::string &directory);
Block createBlockFromInputFile(const std::string &filePath);
std::string writeCompressedResult(const std::deque<std::deque<std::deque<Cuboid>>> &compressedResult);

#endif // INPUT_TEST_H
