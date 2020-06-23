#ifndef PARSER_STMT_H
#define PARSER_STMT_H

#include <string>
#include <vector>

using namespace std;


namespace parser
{
    extern bool check_statements(const vector<string> &tokens);
    extern bool wait_cv_statement(string stmt);
    extern void check_in_struct_end(string & outline);
    extern string get_stmt_lines();

    extern string do_constructor(const string & varName, vector<string> & tokens);
    extern string do_statement_routine(vector<string> &tokens, size_t indents, const vector<string> & flags);
    extern void stmt_clear();
};

#endif // PARSER_STMT_H
