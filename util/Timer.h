#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

class Timer
{
public:
    void elapsed();
private:
    std::chrono::time_point<std::chrono::steady_clock>
    start {std::chrono::steady_clock::now()};
};

#endif

