#ifndef MULTITHREADSHANDLER_H
#define MULTITHREADSHANDLER_H

class MultiThreadsHandler
{
private:
    /*
    isWriting
    threadCount
    */
    static void startReadingThread();
    static void startWritingThread();
    static void startCompressingThread();

public:
    MultiThreadsHandler(/* args */);
    ~MultiThreadsHandler();
    static void startThreads();
};

#endif