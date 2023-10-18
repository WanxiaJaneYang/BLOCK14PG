#include <iostream>
#include <sstream>

#ifndef MULTITHREADSHANDLER_H
#define MULTITHREADSHANDLER_H

void startThreads();
static void startReadingThread();
static void startWritingThread();
static void startCompressingThread();
std::string getHighPrecisionTimestamp();
#endif