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

void startThreads()
{
    ThreadPool pool(7); // 3 for 4 core, 7 for 8 core
    readInputRunning = true;
    // {
    //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Reading thread started..." << std::endl;
    // }
    pool.enqueue(startReadingThread);

    while (true)
    {
        int maxTasks = readInputRunning ? 5 : 6;

        // assign available threads to compressor reserving one for writing
        if (GlobalVars::processTasks.size() > 0)
        {
            // {
            //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
            //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] processTasks.size(): " << GlobalVars::processTasks.size() << std::endl;
            // }
            while (maxTasks > compressionTasksCount.load())
            {
                compressionTasksCount.fetch_add(1);
                // {
                //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
                //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Compressing thread started " << std::endl;
                // }
                pool.enqueue(startCompressingThread);
            }
        }

        // use only one thread for writing
        if (GlobalVars::newBlockCompressedSingnal.load() && !outputRunning)
        {
            GlobalVars::newBlockCompressedSingnal.store(false);
            outputRunning = true;
            // {
            //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
            //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Writing thread started..." << std::endl;
            // }
            pool.enqueue(startWritingThread);
        }
        // Exit condition for the infinite loop: nothing to do
        if (!readInputRunning && GlobalVars::processTasks.size() == 0 && compressionTasksCount.load() == 0 && !GlobalVars::newBlockCompressedSingnal.load() && !outputRunning)
        {
            // sleep for 100 ms in case any gap
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (!readInputRunning && GlobalVars::processTasks.size() == 0 && compressionTasksCount.load() == 0 && !GlobalVars::newBlockCompressedSingnal.load() && !outputRunning)
            {
                break;
            }
        }
    }
}

static void startReadingThread()
{

    readInput(); // call the original readInput function
    readInputRunning = false;
    // {
    //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Reading thread exited." << std::endl;
    // }
}

static void startWritingThread()
{

    output();
    outputRunning = false;
    // {
    //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Writing thread exited." << std::endl;
    // }
}

static void startCompressingThread()
{
    std::thread::id this_id = std::this_thread::get_id();
    // {
    //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Compressing thread ID: " << this_id << "compressor threads number:" << compressionTasksCount << std::endl;
    // }
    compress();
    compressionTasksCount.fetch_sub(1);

    // {
    //     std::lock_guard<std::mutex> lock(GlobalVars::coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Compressing thread ID: " << this_id << "compressor threads number:" << compressionTasksCount << std::endl;
    // }
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
