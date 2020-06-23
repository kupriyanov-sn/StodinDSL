#ifndef __STODIN_COMMON_H
#define __STODIN_COMMON_H
#include<iostream>
#include<exception>
#include<vector>
#include<string>
#include <cstdint>
#include "__stodin_string.h"
#include "__stodin_array.h"

using namespace std;
//https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow

extern ostream& operator<<(ostream& os, const exception& ex);
extern vector<string> __stodinTrace;
extern void _stodin_parse_args(int argc, char** argv);
extern void get_application_arg(__stodin_string & res, int64_t idx);
extern void get_all_application_args(__stodin_array<__stodin_string> & res);

#endif // __STODIN_COMMON_H
