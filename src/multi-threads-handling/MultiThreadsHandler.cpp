#include "MultiThreadsHandler.h"
#include "../input/readInput.h"
#include "../output/output.h"
#include "../compressor/Compressor.h"
#include <thread>

const int MAX_THREADS = 8;

void startThreads()
{
    // just a stub, waiting for the implementation of the threads
    startReadingThread();

    std::vector<std::thread> threads;
    for (int i = 0; i < MAX_THREADS; ++i)
    {
        threads.emplace_back(startCompressingThread);
    }

    for (auto &t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
    // output();
}

static void startReadingThread()
{
    std::thread readerThread(readInput);
    readerThread.detach();
}

static void startCompressingThread()
{
    Compressor::compress();
    output();
}

// static void startWritingThread()
// {
// }
