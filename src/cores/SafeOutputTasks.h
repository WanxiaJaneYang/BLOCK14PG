#include <vector>
#include <mutex>
#include "Cuboid.h"
#include <deque>

#ifndef SAFEOUTPUTTASKS_H
#define SAFEOUTPUTTASKS_H

class SafeOutputTasks
{
#ifdef TEST
public:
    std::vector<std::deque<std::deque<Cuboid>>>tasks;
#else
private:
    std::vector<std::deque<std::deque<Cuboid>>>tasks;
#endif // end of TEST

    std::mutex mtx;

public:
    SafeOutputTasks();
    int size();
    void push(const std::deque<std::deque<Cuboid>>& cuboids);
    bool pop(std::deque<std::deque<Cuboid>>& cuboids);
    virtual ~SafeOutputTasks();
};

#endif // end of SAFEOUTPUTTASKS_H
