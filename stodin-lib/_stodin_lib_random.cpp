#include "_stodin_lib_random.h"
#include <cstdlib>
#include <ctime>

namespace _stodin_lib_random
{
    static bool randNotInitialized = true;
    void randint(int64_t & res, int64_t startPos, int64_t endPos)
    {
        if(randNotInitialized)
        {
            std::srand(unsigned(std::time(0)));
            randNotInitialized = false;
        }
        res = startPos + rand() % (endPos - startPos + 1);
    }
    void choice(int64_t & res, const __stodin_array<int64_t> & arr)
    {
        int64_t index = 0;
        int64_t sz = 0;
        size(sz, arr);
        randint(index, 0, sz - 1);
        copy_elem(res, arr, index);
    }
}
