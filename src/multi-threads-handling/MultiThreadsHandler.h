#include <iostream>
#include <sstream>

#ifndef MULTITHREADSHANDLER_H
#define MULTITHREADSHANDLER_H

void startThreads(std::istream &in=std::cin);
static void startReadingThread(std::istream &in = std::cin);
static void startWritingThread();
static void startCompressingThread();
std::string getHighPrecisionTimestamp();
#endif