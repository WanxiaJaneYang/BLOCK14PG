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
#include <algorithm>
#include <ostream>

std::vector<std::string> listInputFiles(const std::string& directory);

std::istringstream simulateInputStream(const std::string& filePath);

class StreamRedirector {
    std::ostream& stream_;
    std::streambuf* oldBuf_;
public:
    inline StreamRedirector(std::ostream& stream, std::streambuf* newBuf) : stream_(stream), oldBuf_(stream.rdbuf(newBuf)) {}
    inline ~StreamRedirector() { stream_.rdbuf(oldBuf_); }
};

std::vector<std::string> sortedLinesFromStream(std::istream& stream);

#endif 
