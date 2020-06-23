#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

namespace parser
{
    extern bool parse(string line, string & outline, const vector<string> & flags);
    extern string get_func_lines();
    extern void clear_data();

    extern vector<string> get_modules();
    extern vector<string> get_lib_modules();
    extern vector<string> get_cpp_modules();

    extern string get_module_headers();
}

#endif // PARSER_H_INCLUDED
