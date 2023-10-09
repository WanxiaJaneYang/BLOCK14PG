#include "MultiThreadsHandler.h"
#include "../input/readInput.h"
#include "../output/output.h"
#include "../compressor/Compressor.h"
#include "../globals/globals.h"
#include <atomic>
#include <thread>
#include "ThreadPool.h"

bool readInputRunning = false;
bool outputRunning = false;
std::atomic<int> compressionTasksCount(0);

void startThreads()
{
    ThreadPool pool(7); // 8 threads being used in total, but 1 has been used by main process

    readInputRunning = true; // set the flag to indicate that readInput is running
    pool.enqueue(startReadingThread); // use 1 thread to read input at the beginning

    while (readInputRunning) // 6 threads available now
    {
        if (GlobalVars::processTasks.size() > 0)
        {
            for (int i = 0; i < (5 - compressionTasksCount.load()); ++i) // reserve a thread for output, use out 5 threads left
            {
                compressionTasksCount++;
                pool.enqueue(startCompressingThread);
            }
        }

        if (GlobalVars::outputTasks.size() > 0 && !outputRunning) // got something to output
        {
            outputRunning = true;
            pool.enqueue(startWritingThread);
        }

        // Prevent any busy-waiting even tho it's kinda impossible in our senario
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // inside the loop
    }

    // after readInput finishes, we have one more thread to compress the remaining tasks
    if (GlobalVars::processTasks.size() > 0)
        {
            for (int i = 0; i < (6 - compressionTasksCount.load()); ++i) // reserve a thread for output, use out 5 threads left
            {
                compressionTasksCount++;
                pool.enqueue(startCompressingThread);
            }
        }

    // ThreadPool's destructor will wait for all tasks to complete before the main function exits
}

static void startReadingThread()
{
    std::cout << "[DEBUG] Reading thread started..." << std::endl;
    readInput(); // call the original readInput function
    readInputRunning = false;
    std::cout << "[DEBUG] Reading thread exited." << std::endl;
}

static void startWritingThread()
{
    std::cout << "[DEBUG] Writing thread started..." << std::endl;
    output();
    outputRunning = false;
    std::cout << "[DEBUG] Writing thread exited." << std::endl;
}

static void startCompressingThread()
{
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "[DEBUG] Compressing pipeline started in thread ID: " << this_id << std::endl;
    
    Compressor::compress();
    compressionTasksCount--;
    
    std::cout << "[DEBUG] Compressing pipeline ended in thread ID: " << this_id << std::endl;
}
