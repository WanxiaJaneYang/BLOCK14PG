#include "MultiThreadsHandler.h"
#include "../input/readInput.h"
#include "../output/output.h"
#include "../compressor/Compressor.h"
#include <thread>
#include <iostream>

using namespace std;

void startThreads()
{
    // just a stub, waiting for the implementation of the threads
    cout << "input read" << endl;
    readInput("input.txt");
    cout << "compressing" << endl;
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
