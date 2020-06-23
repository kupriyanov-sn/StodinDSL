#include <vector>
#include <iostream>
#include "parser_error.h"

namespace parser_error
{
    static vector<string> _errors;
    static string _module;
    static string _lineNumber;

    void add(string message)
    {
        string m = string("#Error! ") + _module + ", " + _lineNumber + ": " + message;
        _errors.push_back(m);
    }

    void set_line(string module, int lineNumber)
    {
        _module = module;
        _lineNumber = std::to_string(lineNumber);
    }

    string get_line_number()
    {
        return _lineNumber;
    }

    string get_module()
    {
        return _module;
    }

    bool has_no_errors()
    {
        return _errors.empty();
    }

    void print_errors()
    {
        for(auto s: _errors)
        {
            cout << s << endl;
        }
    }
};
