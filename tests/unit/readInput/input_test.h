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

std::vector<std::string> listInputFiles(const std::string& directory);

#endif // INPUT_TEST_H
