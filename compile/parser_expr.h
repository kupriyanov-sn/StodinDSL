#ifndef PARSER_EXPR_H
#define PARSER_EXPR_H

#include <string>
#include <vector>

using namespace std;

namespace parser
{
    extern string do_expr_routine(vector<string> &tokens, const vector<string> & flags);
    extern bool check_expr(const vector<string> &tokens);
};

#endif // PARSER_EXPR_H
