#include "MultiThreadsHandler.h"
#include "../input/readInput.h"
#include "../output/output.h"
#include "../compressor/Compressor.h"
#include <iostream>
using namespace std;

MultiThreadsHandler::MultiThreadsHandler(/* args */)
{
}

MultiThreadsHandler::~MultiThreadsHandler()
{
}

void MultiThreadsHandler::startThreads()
{
    // just a stub, waiting for the implementation of the threads
    // cout << "Reading..." << endl;
    readInput();
    // cout << "Input read successfully\n"
    //      << endl;
    // cout << "process tasks size = " << GlobalVars::processTasks.size() << endl;
    Compressor::compress();
    // cout << "Compressed successfully\n"
    //      << endl;
    // cout << "output tasks size = " << GlobalVars::outputTasks.size() << endl;
    output();
}

void MultiThreadsHandler::startReadingThread()
{
}

void MultiThreadsHandler::startWritingThread()
{
}

void MultiThreadsHandler::startCompressingThread()
{
}
