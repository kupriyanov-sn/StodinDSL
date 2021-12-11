#include "_stodin_lib_math.h"
#include <cmath>
#include <limits>

namespace _stodin_lib_math
{
    void sqrt(double & res, const double arg)
    {
        res = ::sqrt(arg);
    }

    void abs(int64_t & res)
    {
        if(res < 0) res = -res;
    }
    
    void abs(int64_t & res, const int64_t x)
    {
        res = x >= 0 ? x : -x;

    }
    
    void fabs(double & res, const double x)
    {
        res = ::fabs(x);
    }

    void fdiff(double & res, const double x, const double y)
    {
        res = ::fabs(x - y);
    }

    void float_compare(__stodin_bool & res, const double x, const double y, const double percent)
    {
        double epsilon = std::numeric_limits<double>::epsilon();
        if((y > epsilon) || (y < -epsilon))
            res = ::fabs(1 - x / y) < (percent / 100.0);
        else
            res = (x <= epsilon) && (x >= -epsilon);
    }
};
