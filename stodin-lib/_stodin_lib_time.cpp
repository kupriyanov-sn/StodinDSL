#include "_stodin_lib_time.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

namespace _stodin_lib_time
{
    void time(int64_t & res)
    {
        time_t t = 0;
        std::time(&t);
        res = static_cast<int64_t>(t);
    }
    
    void ms_clock(int64_t & res)
    {
        clock_t t = clock();
        res = static_cast<int64_t>(t) / (static_cast<int64_t>(CLOCKS_PER_SEC / 1000));
    }
    
    void ms_sleep(const int64_t delta)
    {
        std::this_thread::sleep_for (std::chrono::milliseconds(delta));
    }
    
    void us_sleep(const int64_t delta)
    {
        std::this_thread::sleep_for (std::chrono::microseconds(delta));
    }
}
