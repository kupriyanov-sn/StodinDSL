#include "_stodin_lib_time.h"
#include <cstdlib>
#include <ctime>

namespace _stodin_lib_time
{
    void time(int64_t & res)
    {
        time_t t = 0;
        std::time(&t);
        res = static_cast<int64_t>(t);
    }
}
