#ifndef __STODIN_SAFE_H
#define __STODIN_SAFE_H

#include<iostream>
#include<exception>
#include <limits>
#include <cmath>
#include "__stodin_types.h"

using namespace std;
//https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

template<typename T0, class = typename std::enable_if<!std::is_arithmetic<T0>::value>::type>
inline void __stodin_plus(T0 & res, char ta)
{
    res += ta;
}

template<typename T0, class = typename std::enable_if<!std::is_arithmetic<T0>::value>::type>
inline void __stodin_plus(T0 & res, const char * ta)
{
    res += ta;
}

template<typename T0, class = typename std::enable_if<!std::is_arithmetic<T0>::value>::type>
inline void __stodin_plus(T0 & res, const T0 ta)
{
    res += ta;
}

template<typename T0, class = typename std::enable_if<!std::is_arithmetic<T0>::value>::type, typename T1>
inline void __stodin_plus(T0 & res, const T1 ta)
{
    res += ta;
}

template <typename T0, typename T1>
void __stodin_plus(T0 & res, const T1 ta)
{
    if((!numeric_limits<T0>::is_signed) && (ta < 0))
        throw domain_error("Addition error. Sign is incorrect!");

    T0 a = static_cast<T0>(ta);
    if (((res > 0) && (a > (numeric_limits<T0>::max() - res))) ||
            ((res < 0) && (a < (numeric_limits<T0>::min() - res))))
    {
        throw domain_error("Addition error. Overflow!");
    }
    else
    {
        res += a;
    }
}

template <typename T0, typename T1>
void __stodin_minus(T0 & res, const T1 ta)
{
    if((!numeric_limits<T0>::is_signed) && (ta < 0))
        throw domain_error("Subtraction error. Sign is incorrect!");

    T0 a = static_cast<T0>(ta);

    if ((a > 0 && res < numeric_limits<T0>::min() + a) ||
            (a < 0 && res > numeric_limits<T0>::max() + a))
    {
        throw domain_error("Subtraction error. Overflow!");
    }
    else
    {
        res -= a;
    }
}

template <typename T0, typename T1>
void __stodin_mult(T0 & res, const T1 ta)
{
    if((!numeric_limits<T0>::is_signed) && (ta < 0))
        throw domain_error("Multiplication error. Sign is incorrect!");
    T0 a = static_cast<T0>(ta);
    if(is_floating_point<T0>::value)
    {
        res *= a;
        if(isinf(res))
            throw domain_error("Multiplication error. Infinity!");
        if(isnan(res))
            throw domain_error("Multiplication error. Nan!");
        return;
    }

    if (a > 0)    /* a is positive */
    {
        if (res > 0)    /* a and res are positive */
        {
            if (a > (numeric_limits<T0>::max() / res))
            {
                throw domain_error("Multiplication error. Overflow!");
            }
        }
        else     /* a positive, res nonpositive */
        {
            if (res < (numeric_limits<T0>::min() / a))
            {
                throw domain_error("Multiplication error. Overflow!");
            }
        } /* a positive, res nonpositive */
    }
    else     /* a is nonpositive */
    {
        if (res > 0)   /* a is nonpositive, res is positive */
        {
            if (a < (numeric_limits<T0>::min() / res))
            {
                throw domain_error("Multiplication error. Overflow!");
            }
        }
        else     /* a and res are nonpositive */
        {
            if ( (a != 0) && (res < (numeric_limits<T0>::max() / a)))
            {
                throw domain_error("Multiplication error. Overflow!");
            }
        } /* End if a and res are nonpositive */
    } /* End if a is nonpositive */

    res *= a;
}

template <typename T0, typename T1>
void __stodin_div(T0 & res, const T1 ta)
{
    if((!numeric_limits<T0>::is_signed) && (ta < 0))
        throw domain_error("Division error. Sign is incorrect!");
    T0 a = static_cast<T0>(ta);
    if(is_floating_point<T0>::value)
    {
        res /= a;
        if(isinf(res))
            throw domain_error("Division error. Infinity!");
        if(isnan(res))
            throw domain_error("Division error. NaN!");
        return;
    }

    if (a == 0)
    {
        throw domain_error("Zero division error!");
    }
    else if((res == numeric_limits<T0>::min()) && (a == static_cast<T0>(-1)))
    {
        throw domain_error("Division error. Overflow!");
    }
    else
    {
        res /= a;
    }
}


template <typename T0, typename T1>
void __stodin_rem(T0 & res, const T1 ta)
{
    if((!numeric_limits<T0>::is_signed) && (ta < 0))
        throw domain_error("Remainder error. Sign is incorrect!");
    T0 a = static_cast<T0>(ta);
    if(is_floating_point<T0>::value)
    {
        res /= a;
        if(isinf(res))
            throw domain_error("Division error. Infinity!");
        if(isnan(res))
            throw domain_error("Division error. NaN!");
        return;
    }
    if (a == 0)
    {
        throw domain_error("Zero division error!");
    }
    else if((res == numeric_limits<T0>::min()) && (a == static_cast<T0>(-1)))
    {
        throw domain_error("Remainder error. Overflow!");
    }
    else
    {
        res %= a;
    }
}

template <typename T0, typename T1>
void __stodin_lshift(T0 & res, const T1 a)
{
    if(a < 0 || res < 0)
        throw domain_error("Left shift error. Sign is incorrect!");
    if ((a >= numeric_limits<T0>::digits) ||
            (res > (numeric_limits<T0>::max() >> a)))
    {
        throw domain_error("Left shift error. Overflow!");
    }
    else
    {
        res <<= a;
    }
}


#endif // __STODIN_SAFE_H
