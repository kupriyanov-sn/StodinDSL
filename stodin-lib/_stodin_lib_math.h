#ifndef _STODIN_LIB_MATH_H
#define _STODIN_LIB_MATH_H

#include "__stodin_types.h"

namespace _stodin_lib_math
{
    void sqrt(double & res, double arg);
    void fabs(double & res, double x);
    void fdiff(double & res, double x, double y);
    void float_compare(__stodin_bool & res, double x, double y, double percent);
};

#endif // _STODIN_LIB_MATH_H
