#include "Timer.h"
#include <chrono>

long Timer::elapsed()
{
    auto now {std::chrono::steady_clock::now()};
    auto elapsed_microsecond
    {
        std::chrono::duration_cast
        <std::chrono::milliseconds>(now - start).count()
    };
    return elapsed_microsecond;
};
