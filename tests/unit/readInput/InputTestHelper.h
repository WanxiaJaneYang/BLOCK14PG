#ifndef INPUT_TEST_H
#define INPUT_TEST_H

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

std::vector<std::string> listInputFiles(const std::string& directory);
std::string writeContentOfTasks(SafeInputTasks& tasks);
std::string writeContentOfBlock(Block& block);
std::string writeReadContent();

#endif // INPUT_TEST_H
