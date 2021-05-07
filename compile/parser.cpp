#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "lexer.h"
#include "parser.h"
#include "parser_check.h"
#include "parser_ops.h"
#include "parser_stmt.h"
#include "parser_expr.h"
#include "parser_error.h"

using namespace std;
namespace parser
{

static vector<string> modules;
static vector<string> cppModules;
static vector<string> libModules;

size_t previousIndents = 0;

bool parse(string line, string & outline, const vector<string> & flags)
{
    vector<string> tokens = vector<string>();
    string errorString = "";
    size_t indents = 0;
    outline = "";
    try
    {
        if(lexer::get_tokens(line, tokens, indents, errorString))
        {
            if(tokens.size() == 0)
                return true;
            if((tokens.size() > 1) && (tokens[0] == "import"))
            {
                if((tokens[1] == "^") && (tokens.size() > 2))
                    modules.push_back(tokens[2]);
                else if((tokens[1] == "^cpp") && (tokens.size() > 2))
                    cppModules.push_back(tokens[2]);
                else
                    libModules.push_back(tokens[1]);
                return true;
            }

            string indentStr = "";
            for(size_t i = 0; i < indents; ++i)
                indentStr += "    ";
            if(wait_cv_statement(tokens[0]))
            {
                outline += "){\n" + indentStr;
            }
            if(previousIndents > indents)
            {
                for(size_t i = 0; i < (previousIndents - indents); ++i)
                    outline += "}";
                if(indents == 0)
                {
                    check_in_struct_end(outline);
                }
                outline += "\n" + indentStr;
                clear_case_vars(tokens, indents);
            }
            previousIndents = indents;

            if(check_statements(tokens))
            {
                outline += do_statement_routine(tokens, indents, flags);
            }
            else if(check_expr(tokens))
            {
                outline += do_expr_routine(tokens, flags);
            }
            else if(tokens.size() && tokens[0].size())
            {
                parser_error::add(line);
                return false;
            }

            if(outline.size())
                outline = indentStr + outline;

            return true;
        }
        else
        {
            parser_error::add(errorString);
            return false;
        }
    }
    catch(...)
    {
        parser_error::add(line);
        return false;
    }
    return true;
}

string get_func_lines()
{
    return get_stmt_lines();
}

vector<string> get_modules()
{
    return modules;
}

vector<string> get_lib_modules()
{
    return libModules;
}
vector<string> get_cpp_modules()
{
    return cppModules;
}


string get_module_headers()
{
    string res = "";
    for(string module: modules)
        res += "#include \"_stodin_module_" + module + ".h\"\n";
    for(string module: cppModules)
        res += "#include \"_stodin_module_" + module + ".h\"\n";
    for(string module: libModules)
        res += "#include \"_stodin_lib_" + module + ".h\"\n";

    for(string module: modules)
        res += "using namespace _stodin_module_" + module + ";\n";
    for(string module: cppModules)
        res += "using namespace _stodin_module_" + module + ";\n";
    for(string module: libModules)
        res += "using namespace _stodin_lib_" + module + ";\n";
    return res;
}

void clear_data()
{
    stmt_clear();
    modules.clear();
    cppModules.clear();
    libModules.clear();
}
}
