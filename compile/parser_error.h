#ifndef PARSER_ERROR_H
#define PARSER_ERROR_H
#include <string>

using namespace std;

namespace parser_error
{
    void add(string message);
    void set_line(string module, int lineNumber);
    string get_line_number();
    string get_module();
    bool has_no_errors();
    void print_errors();
};

#endif // PARCER_ERROR_H
