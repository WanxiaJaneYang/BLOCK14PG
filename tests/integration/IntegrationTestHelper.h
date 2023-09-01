#ifndef INTEGRATION_TEST_H
#define INTEGRATION_TEST_H

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include "../../../src/input/readInput.h"
#include "../../../src/cores/SafeInputTasks.h"
#include "../../../src/globals/globals.h"
#include "../../../src/cores/Block.h"
#include "../../../src/cores/Cuboid.h"
#include "../../../src/compressor/Compressor.h"
#include "../../../src/output/output.h"
#include "../../../src/multi-threads-handling/MultiThreadsHandler.h"
#include <thread>

std::vector<std::string> listInputFiles(const std::string& directory);
std::string writeContentOfTasks(SafeInputTasks& tasks);
std::string writeContentOfBlock(Block& block);
std::string writeReadContent();
void clearTasks(SafeInputTasks& tasks);

#endif 
