#ifndef PARSER_CHECK_H
#define PARSER_CHECK_H

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace parser
{
    extern bool is_string(string token);
    extern bool is_int(const string& token);
    extern bool is_double(const string& token);
    extern bool is_bool(const string& token);
    extern string check_enum(string res);
    extern string check_aggregate(const string op, const bool creating = false);
    extern string check_module(string op);
    extern string check_common_type(string tStr);
    extern string get_type(string typeName);

};

#endif // PARSER_CHECK_H
