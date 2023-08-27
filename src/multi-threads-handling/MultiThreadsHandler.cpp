#include "MultiThreadsHandler.h"
#include "../input/readInput.h"
#include "../output/output.h"
#include "../compressor/Compressor.h"
#include <thread>

void startThreads()
{
    // just a stub, waiting for the implementation of the threads
    readInput("input.txt");
    Compressor::compress();
    output();
}

static void startReadingThread()
{
}

static void startWritingThread()
{
}

static void startCompressingThread()
{
}
