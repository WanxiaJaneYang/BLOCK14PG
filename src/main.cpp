#include "multi-tasks-handling/MultiThreadsHandler.h"
#include "globals/globals.h"

int main()
{
    GlobalVars::inputFileName = "input.txt";
    GlobalVars::outputFileName = "output.txt";

    MultiThreadsHandler::startThreads();
    return 0;
}