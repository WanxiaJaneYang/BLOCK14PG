#include "MultiThreadsHandler.h"
#include "../input/readInput.h"
#include "../output/output.h"
#include "../compressor/Compressor.h"
#include <thread>
#include "ThreadPool.h" 

void startThreads()
{
    // Start dedicated threads for input and output
    std::thread inputThread(readInput);
    std::thread outputThread(output); // I need a function never ends
    
    inputThread.detach();
    outputThread.detach();
    
    ThreadPool pool(6);
    
    pool.enqueue(readInput);
    pool.enqueue(output);
    pool.enqueue(startWritingThread)
    
      for (int i = 0; i < 6; ++i)
        {
            pool.enqueue(Compressor::compress);
        }
    
    inputThread.join();
    outputThread.join();
    
    // ThreadPool's destructor will wait for all tasks to complete before the main function exits
}
