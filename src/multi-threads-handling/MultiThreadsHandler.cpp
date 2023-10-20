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

void startThreads()
{
    startReadingThread();
    startCompressingThread();
    startWritingThread();
    // ThreadPool pool(3); // 3 for 4 core, 7 for 8 core
    // readInputRunning = true;
    // pool.enqueue(startReadingThread);

    // while (true)
    // {
    //     if (GlobalVars::processTasks.size() > 0)
    //     {
    //         int maxTasks = readInputRunning ? 1 : 2; // 5 : 6
    //         for (int i = 0; i < (maxTasks - compressionTasksCount.load()); ++i)
    //         {
    //             compressionTasksCount++;
    //             pool.enqueue(startCompressingThread);
    //         }
    //     }

    //     if (GlobalVars::outputTasks.size() > 0 && !outputRunning)
    //     {
    //         outputRunning = true;
    //         pool.enqueue(startWritingThread);
    //     }

    //     // Exit condition for the infinite loop
    //     if (!readInputRunning && GlobalVars::processTasks.size() == 0 && compressionTasksCount.load() == 0 && GlobalVars::outputTasks.size() == 0 && !outputRunning)
    //         break;
    // }
}

static void startReadingThread()
{
    // {
    //     std::lock_guard<std::mutex> lock(coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Reading thread started..." << std::endl;
    // }
    readInput(); // call the original readInput function
    readInputRunning = false;
    // {
    //     std::lock_guard<std::mutex> lock(coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Reading thread exited." << std::endl;
    // }
}

static void startWritingThread()
{
    // {
    //     std::lock_guard<std::mutex> lock(coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Writing thread started..." << std::endl;
    // }
    output();
    outputRunning = false;
    // {
    //     std::lock_guard<std::mutex> lock(coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Writing thread exited." << std::endl;
    // }
}

static void startCompressingThread()
{
    // std::thread::id this_id = std::this_thread::get_id();
    // {
    //     std::lock_guard<std::mutex> lock(coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Compressing pipeline started std::cin thread ID: " << this_id << "compressor threads number:" << compressionTasksCount << std::endl;

    // }
    compress();
    compressionTasksCount--;

    // {
    //     std::lock_guard<std::mutex> lock(coutMutex);
    //     std::cout << getHighPrecisionTimestamp() << "[DEBUG] Compressing pipeline ended std::cin thread ID: " << this_id << "compressor threads number:" << compressionTasksCount << std::endl;
    // }
}

// std::string getHighPrecisionTimestamp()
// {
//     // Get the current time with high precision
//     auto now = std::chrono::high_resolution_clock::now();
//     auto seconds_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
//     auto fraction_seconds_since_epoch = now.time_since_epoch() - seconds_since_epoch;

//     // Format high precision time into a string
//     std::ostringstream oss;
//     oss << seconds_since_epoch.count() << "."
//         << std::setw(9) << std::setfill('0')
//         << fraction_seconds_since_epoch.count();

//     return oss.str();
// }
