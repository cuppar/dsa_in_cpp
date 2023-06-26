#include "Timer.h"
#include <chrono>

void Timer::elapsed()
{
    auto now {std::chrono::steady_clock::now()};
    auto elapsed_microsecond
    {
        std::chrono::duration_cast
        <std::chrono::milliseconds>(now - start).count()
    };
    std::cout << "Elapsed " << elapsed_microsecond << " ms.\n";
};
