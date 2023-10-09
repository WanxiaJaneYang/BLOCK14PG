#include <vector>
#include <mutex>
#include "Cuboid.h"

#ifndef SAFEOUTPUTTASKS_H
#define SAFEOUTPUTTASKS_H

class SafeOutputTasks
{
#ifdef TEST
public:
    std::vector<Cuboid> tasks;
#else
private:
    std::vector<Cuboid> tasks;
#endif // end of TEST

    std::mutex mtx;

public:
    SafeOutputTasks();
    int size();
    void push(const Cuboid &cuboid);
    bool pop(Cuboid &cuboid);
    virtual ~SafeOutputTasks();
};

#endif // end of SAFEOUTPUTTASKS_H
