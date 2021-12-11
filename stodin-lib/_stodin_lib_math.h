#ifndef _STODIN_LIB_MATH_H
#define _STODIN_LIB_MATH_H

#include "__stodin_types.h"

namespace _stodin_lib_math
{
    void sqrt(double & res, const double arg);
    void abs(int64_t & res);
    void abs(int64_t & res, const int64_t x);
    void fabs(double & res, const double x);
    void fdiff(double & res, const double x, const double y);
    void float_compare(__stodin_bool & res, const double x, const double y, const double percent);
    template <typename T>
    void max(T & res, const T & arg)
    {
        if(res < arg)
            res = arg;
    }
    template <typename T>
    void min(T & res, const T & arg)
    {
        if(res > arg)
            res = arg;
    }
    
};

#endif // _STODIN_LIB_MATH_H
