#include <iostream>
#include <exception>
#include <cwchar>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include "__stodin_string.h"
#include "__stodin_array.h"
#include "__stodin_dict.h"
#include "__stodin_io.h"
#include "_stodin_lib_math.h"
#include "__stodin_common.h"
#include "__stodin_safe.h"

using namespace std;

int main(int argc, char** argv)
{
    __stodin_string s = "Привет\n";
    print("Привет\n");
    print(s);
    return 0;
}
