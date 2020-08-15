#include "_stodin_lib_math.h"
#include <cmath>
#include <limits>

namespace _stodin_lib_math
{
    void sqrt(double & res, double arg)
    {
        res = ::sqrt(arg);
    }

    void fabs(double & res, double x)
    {
        res = ::fabs(x);
    }

    void fdiff(double & res, double x, double y)
    {
        res = ::fabs(x - y);
    }

    void float_compare(__stodin_bool & res, double x, double y, double percent)
    {
        double epsilon = std::numeric_limits<double>::epsilon();
        if((y > epsilon) || (y < -epsilon))
            res = ::fabs(1 - x / y) < (percent / 100.0);
        else
            res = (x <= epsilon) && (x >= -epsilon);
    }
};
