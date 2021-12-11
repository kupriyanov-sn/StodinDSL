#ifndef _STODIN_LIB_TIME_H
#define _STODIN_LIB_TIME_H

#include <cstdint>

namespace _stodin_lib_time
{
    extern void time(int64_t & res);
    extern void ms_clock(int64_t & res);
    extern void ms_sleep(const int64_t delta);
    extern void us_sleep(const int64_t delta);
}

#endif // _STODIN_LIB_TIME_H
