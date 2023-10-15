#include "MultiThreadsHandler.h"
#include "../input/readInput.h"
#include "../output/output.h"
#include "../compressor/Compressor.h"
#include "../globals/globals.h"
#include <atomic>
#include <thread>
#include "ThreadPool.h"
#include <mutex>
#include <chrono>
#include <iomanip>

bool readInputRunning = false;
bool outputRunning = false;
std::atomic<int> compressionTasksCount(0);
static std::mutex coutMutex; // Define a global mutex for synchronizing std::cout usage

void startThreads(std::istream &in)
{
    //std::cout << getHighPrecisionTimestamp() << "[DEBUG] Main thread started, ID: " << std::this_thread::get_id() << std::endl;
    ThreadPool pool(7); // 8 threads being used in total, but 1 has been used by main process

    //std::cout << getHighPrecisionTimestamp() << "[DEBUG] ThreadPool created, ID: " << std::this_thread::get_id() << std::endl;
    readInputRunning = true; // set the flag to indicate that readInput is running
    pool.enqueue([&in]()
                 { startReadingThread(in); }); // lambda: use 1 thread to read input at the beginning

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
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // inside the loop
    }
    while (GlobalVars::processTasks.size() > 0)
    // after readInput finishes, we have one more thread to compress the remaining tasks
    {
        for (int i = 0; i < (6 - compressionTasksCount.load()); ++i) // reserve a thread for output, use out 5 threads left
        {
            compressionTasksCount++;
            pool.enqueue(startCompressingThread);
        }

        if (GlobalVars::outputTasks.size() > 0 && !outputRunning) // got something to output
        {
            outputRunning = true;
            pool.enqueue(startWritingThread);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // inside the loop
    }
    
    // un-implemented 7 threads for output
    while (GlobalVars::outputTasks.size() > 0 && !outputRunning)
    {
        outputRunning = true;
        pool.enqueue(startWritingThread);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // inside the loop
    }

    // ThreadPool's destructor will wait for all tasks to complete before the main function exits
}

static void startReadingThread(std::istream &in)
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        //std::cout << getHighPrecisionTimestamp() << "[DEBUG] Reading thread started..." << std::endl;
    }
    readInput(in); // call the original readInput function
    readInputRunning = false;
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        //std::cout << getHighPrecisionTimestamp() << "[DEBUG] Reading thread exited." << std::endl;
    }
}

static void startWritingThread()
{
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        //std::cout << getHighPrecisionTimestamp() << "[DEBUG] Writing thread started..." << std::endl;
    }
    output();
    outputRunning = false;
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        //std::cout << getHighPrecisionTimestamp() << "[DEBUG] Writing thread exited." << std::endl;
    }
}

static void startCompressingThread()
{
    std::thread::id this_id = std::this_thread::get_id();
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        //std::cout << getHighPrecisionTimestamp() << "[DEBUG] Compressing pipeline started in thread ID: " << this_id << std::endl;
    }
    compress();
    compressionTasksCount--;

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        //std::cout << getHighPrecisionTimestamp() << "[DEBUG] Compressing pipeline ended in thread ID: " << this_id << std::endl;
    }
}

std::string getHighPrecisionTimestamp()
{
    // Get the current time with high precision
    auto now = std::chrono::high_resolution_clock::now();
    auto seconds_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    auto fraction_seconds_since_epoch = now.time_since_epoch() - seconds_since_epoch;

    // Format high precision time into a string
    std::ostringstream oss;
    oss << seconds_since_epoch.count() << "."
        << std::setw(9) << std::setfill('0')
        << fraction_seconds_since_epoch.count();

    return oss.str();
}
