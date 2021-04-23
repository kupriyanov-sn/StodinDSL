#ifndef _STODIN_LIB_RANDOM_H
#define _STODIN_LIB_RANDOM_H
#include <cstdint>
#include "__stodin_array.h"

namespace _stodin_lib_random
{
    extern void randint(int64_t & res, int64_t startPos, int64_t endPos);
    extern void choice(int64_t & res, const __stodin_array<int64_t> & arr);

    template <typename T>
    void shuffle(__stodin_array<T> &data)
    {
        int64_t sz = 0; size(sz, data); sz-=2;
        for(int64_t i = sz; i > -1; i += -1)
        {
            int64_t j  {i};j += 1; randint(j, 0, j);
            T tmp  {data.at(i)};
            data.at(i) = data.at(j);
            data.at(j) = tmp;
        }
    }
}

#endif // _STODIN_LIB_RANDOM_H
