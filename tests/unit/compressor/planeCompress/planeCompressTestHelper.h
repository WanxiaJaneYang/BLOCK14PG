#ifndef BLOCK_COMPRESS_TEST_H
#define BLOCK_COMPRESS_TEST_H

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <filesystem>
#include "../../../src/compressor/Compressor.h"
#include "../../../src/cores/SafeOutputTasks.h"
#include "../../../src/globals/globals.h"

std::vector<std::string> listInputFiles(const std::string &directory);
std::deque<std::deque<std::deque<Cuboid>>> convertFileContentToLines(const std::string &fileContent);
std::string writeContentOfTasks(SafeInputTasks &tasks);
std::string writeContentOfCuboid(Cuboid &cuboid);
std::string writeReadContent();
void clearTasks(SafeInputTasks &tasks);

#endif
