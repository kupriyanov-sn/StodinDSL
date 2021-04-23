#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>


#include "parser_stmt.h"
#include "parser_check.h"
#include "parser_ops.h"
#include "parser_error.h"

namespace parser
{

const vector<string> statements = {
    "if", "ifnot", "elif", "else", "for", "in", "break", "continue",
    "return", "def", "mref", "cref", "thread",
    "typedef", "struct", "const", "enum",
    "try", "catch", "throw", "assert",
    "."
};

static bool inStruct = false;
static bool waitCvStatement = false;
static bool mvStatementFlag = false;
static bool staticDef = false;
static vector<string> funcLines;
static vector<string> typeLines;

bool check_statements(const vector<string> &tokens)
{
    return std::find(statements.begin(), statements.end(), tokens[0]) != statements.end();
}

bool wait_cv_statement(string stmt)
{
    if((waitCvStatement == true) && (stmt != "cref") && (stmt != "mref"))
    {
        if((!inStruct) && (!staticDef))
            funcLines.push_back(");");
        waitCvStatement = false;
        mvStatementFlag = false;
        return true;
    }
    return false;
}

void check_in_struct_end(string & outline)
{
    if(inStruct)
    {
        outline = "";
        inStruct = false;
        if(staticDef)
            outline += "};";
        else
            typeLines.push_back("};");
    }
}

string get_stmt_lines()
{
    string res = "";
    for(auto e: typeLines)
    {
        res += e + "\n";
    }
    for(size_t i = 0; i < funcLines.size(); ++i)
    {
        res += funcLines[i];
        if(funcLines[i].back() == ';')
            res += "\n";

    }
    return res;
}


string make_cv_def_line(const vector<string> &tokens, string endSymbol)
{
    string outline = "";
    if(mvStatementFlag)
        outline += ", ";
    for(size_t i = 1; i < tokens.size(); ++i)
    {
        string argDef = tokens[i];
        size_t pos = argDef.find(':');
        if(pos == string::npos)
            parser_error::add(string("invalid argument: ") + argDef);
        string inArg = argDef.substr(0, pos);
        string inType = argDef.substr(pos + 1);
        inType = get_type(inType);
        outline += "const " + inType + " &" + inArg;
        if(i != (tokens.size() - 1))
            outline += ", ";
    }
    outline += ")" + endSymbol;
    return outline;
}

string make_mv_def_line(const vector<string> &tokens)
{
    string outline = "";
    for(size_t i = 1; i < tokens.size(); ++i)
    {
        string argDef = tokens[i];
        size_t pos = argDef.find(':');
        if(pos == string::npos)
            parser_error::add(string("invalid argument: ") + argDef);
        string inArg = argDef.substr(0, pos);
        string inType = argDef.substr(pos + 1);
        inType = get_type(inType);
        outline += inType + " &" + inArg;
        if(i != (tokens.size() - 1))
            outline += ", ";
    }
    return outline;
}

bool has_two_dogs(vector<string> &tokens)
{
    int counter = 0;
    for(auto t : tokens)
    {
        if(t[0] == '@')
            counter++;
    }
    return counter > 1;
}

string do_if_stmt_routine(vector<string> &tokens, bool ifnot = false)
{
    string outline = "";
    string notPrep = ifnot ? "!" : "";
    if(tokens.size() == 2) // if a // with ifnot
    {
        if(is_func_or_operator(tokens[1]))
            parser_error::add("if operator error");
        else
            outline += "if(" + notPrep + check_aggregate(tokens[1]) + "){";
    }
    else if(tokens.size() == 3) // if a b // without ifnot
    {
        if(is_func_or_operator(tokens[1]) || is_func_or_operator(tokens[2]))
            parser_error::add("if operator error");
        else if(ifnot)
            parser_error::add("ifnot cannot be used here, use !=");
        else
            outline += "if(" + check_aggregate(tokens[1]) + " == " + check_aggregate(tokens[2]) + "){";
    }
    else if(tokens.size() == 4)
    {
        if(tokens[2] == "in") // if a in someArray // with ifnot
        {
            string arg = tokens[1];
            string container = check_aggregate(tokens[3]);
            outline += "if(" + notPrep + "(find(" + container + ".begin(), " +
                container + ".end(), " + arg + ") != " + container + ".end())){";
        }
        else // if > a b // without ifnot
        {
            string op = tokens[1];
            string arg1 = tokens[2];
            string arg2 = tokens[3];
            if(is_operator(op) && (!is_func_or_operator(arg1)) && (!is_func_or_operator(arg2)))
                outline += "if(" + check_aggregate(arg1) + " " + op + " " + check_aggregate(arg2) + "){";
            else if(ifnot)
                parser_error::add("ifnot cannot be used here");
            else
                parser_error::add("if operator error");
        }
    }
    else if(has_two_dogs(tokens)) // if *a @bool in a @some_func b c // with ifnot
    {
        string varName = tokens.at(1).substr(1);
        string typeName = get_type(tokens.at(2).substr(1));
        outline += "if(" + typeName + " " + varName + "= 0 + (";
        string funcName = "";
        vector<string> args;
        for(size_t i = 4; i < tokens.size(); ++i)
        {
            if(tokens.at(i).at(0) == '@')
                funcName = check_module(tokens[i].substr(1));
            else
                args.push_back(tokens[i]);
        }
        outline += funcName + "(";
        for(size_t i = 0; i < args.size(); ++i)
        {
            outline += check_aggregate(args[i]);
            if(i < (args.size() - 1))
                outline += ", ";
        }
        outline += "), " + notPrep + varName + ")){";

    }
    else if((tokens.size() > 4) && (tokens[2] == "in") ) // if a in b c d // with ifnot
    {
        string arg = tokens[1];
        outline += "if(" + notPrep + "(";
        for(size_t i = 3; i < tokens.size(); ++i)
        {
            outline += "(" + check_aggregate(arg) + " == " + check_aggregate(tokens[i]) + ")";
            if(i < tokens.size() - 1)
                outline += " || ";
        }
        outline += ")){";
    }
    else
        parser_error::add("if error");
    return outline;
}

string do_for_stmt_routine(vector<string> &tokens)
{
    string outline = "";
    if(tokens.size() < 2)  // for # endless cycle
    {
        outline += "for(;;){";
    }
    else if(tokens.size() == 2)
    {
        if(tokens.at(1) == "1") // for 1 # block
        {
            outline += "{";
        }
        else if(tokens.at(1) == "0") // for 0 # pass
        {
            outline += "{}";
        }
        else // for n # times
        {
            outline += "for(int _stodin_cycle_var_ = 0; _stodin_cycle_var_ < " + check_aggregate(tokens.at(1)) + "; ++_stodin_cycle_var_){";
        }
    }
    else if(has_two_dogs(tokens)) // for *b @bool in b @some_func c
    {
        string varName = tokens.at(1).substr(1);
        string typeName = get_type(tokens.at(2).substr(1));
        outline += "for(" + typeName + " " + varName + ";(";
        string funcName = "";
        vector<string> args;
        for(size_t i = 4; i < tokens.size(); ++i)
        {
            if(tokens.at(i).at(0) == '@')
                funcName = check_module(tokens[i].substr(1));
            else
                args.push_back(tokens[i]);
        }
        outline += funcName + "(";
        for(size_t i = 0; i < args.size(); ++i)
        {
            outline += check_aggregate(args[i]);
            if(i < (args.size() - 1))
                outline += ", ";
        }
        outline += "), " + varName + ");){";

    }
    else
    {
        string varName = tokens.at(1);
        string newVarType = "";
        if(varName.at(0) == '*')
        {
            varName = varName.substr(1);
            string t = tokens.at(2);
            if(t[0] == '@')
            {
                newVarType = get_type(t.substr(1));
                tokens.erase(tokens.begin() + 2);
            }
            else
                newVarType = "auto";
        }
        if((tokens.size() == 8) && (tokens.at(2) == "in") && (tokens.at(4) == ";")) // for *a @int in begin;end;step
        {
            string initVal = tokens.at(3);
            string lastVal = tokens.at(5);
            string incVal = tokens.at(7);
            string compareStr = incVal[0] == '-' ? " > " : " < ";
            outline += "for(" + newVarType + " " + varName + " = " + check_aggregate(initVal) + "; " +
                       varName + compareStr + check_aggregate(lastVal) + "; " + varName + " += " + incVal + "){";
        }
        else if((tokens.size() == 4) && (tokens.at(2)== "in")) // for *a @int in arr
        {
            outline += "for(" + newVarType + " &" + varName + ": " + check_aggregate(tokens.at(3)) + "){";
        }
        else if((tokens.size() > 4) && (tokens.at(2) == "in")) // for *a in b c d
        {
            outline += "for(" + newVarType + " " + varName + ": {";
            for(size_t i = 3; i < tokens.size(); ++i)
            {
                outline += check_aggregate(tokens.at(i));
                if(i != tokens.size() - 1)
                    outline += ", ";
            }
            outline += "}){";
        }
        else
        {
            parser_error::add("for error");
        }
    }
    return outline;
}


string do_constructor(const string & varName, vector<string> & tokens)
{
    string outline = "";

    vector<vector<string> > argsList;
    argsList.push_back(vector<string>());
    for(size_t i = 1; i < tokens.size(); ++i)
    {
        string arg = tokens.at(i);
        if(arg == ";")
        {
            argsList.push_back(vector<string>());
        }
        else if(is_func_or_operator(arg))
            break;
        else
        {
            argsList.back().push_back(arg);
        }
    }

    string typeName = get_type(tokens.at(0).substr(1));

    if(argsList.size() == 1)
    {
        if(argsList.at(0).size() == 0)
        {
            outline += typeName + " " + varName + ";";
        }
        else
        {
            outline += typeName + " " + varName + "  {";
            for(size_t i = 0; i < argsList.at(0).size() - 1; ++i)
            {
                outline += check_aggregate(argsList.at(0).at(i)) + ", ";
            }
            outline += check_aggregate(argsList.at(0).at(argsList.at(0).size() - 1)) + "};";
        }
    }
    else if(typeName.find("__stodin_array") == 0)
    {
        outline += typeName + " " + varName + " {{";
        for(size_t j = 0; j < argsList.size(); ++j)
        {
            for(size_t i = 0; i < argsList.at(j).size() - 1; ++i)
            {
                outline += check_aggregate(argsList.at(j).at(i)) + ", ";
            }
            outline += check_aggregate(argsList.at(j).at(argsList.at(0).size() - 1)) + "}";
            if(j != (argsList.size() - 1))
                outline += ", {";
        }
        outline += "};";
    }
    else
    {
        parser_error::add("constructor error");
    }
    if(inStruct)
    {
        if(staticDef)
            outline = "    " + outline;
        else
        {
            typeLines.push_back("    " + outline);
            outline = "";
        }
    }
    tokens.erase(tokens.begin()); // erase constructor type
    while(tokens.size() && ( !is_func_or_operator(tokens.front()) ) )
        tokens.erase(tokens.begin());
    return outline;
}

static bool _is_static(string token)
{
    return token.at(0) == '_';
}

string do_statement_routine(vector<string> &tokens, size_t indents, const vector<string> & flags)
{
    string outline = "";
    string stmtName = tokens.at(0);
    bool traceFlag = std::find(flags.begin(), flags.end(), string("-trace")) != flags.end();
    if((stmtName == "def") || (stmtName == "struct"))
    {
        if(_is_static(tokens.at(1))) // static
            staticDef = true;
        else
            staticDef = false;
    }

    if(stmtName == "const")
    {
        string name = tokens.at(1);
        tokens.erase(tokens.begin(), tokens.begin() + 2);
        if(_is_static(name))
        {
            outline += "static const " + do_constructor(name, tokens);
        }
        else
        {
            string s = "const " + do_constructor(name, tokens);
            typeLines.push_back(s);
        }
    }
    else if(stmtName == "enum")
    {
        string name = tokens.at(1);
        if(_is_static(name))
        {
            outline += "enum class " + name + ": " + get_type(tokens.at(2).substr(1)) + "{";
            for(size_t i = 3; i < tokens.size(); ++i)
            {
                outline += tokens[i];
                if(i != tokens.size() - 1)
                    outline += ", ";
            }
            outline += "};";
        }
        else
        {
            string s = "enum class " + name + ": " + get_type(tokens.at(2).substr(1)) + "{";
            for(size_t i = 3; i < tokens.size(); ++i)
            {
                s += tokens[i];
                if(i != tokens.size() - 1)
                    s += ", ";
            }
            s += "};";
            typeLines.push_back(s);
        }
    }
    else if(stmtName == "typedef")
    {
        string name = tokens.at(2);
        if(_is_static(name))
        {
            outline += "typedef " + get_type(tokens.at(1)) + " " + name + ";";
        }
        else
        {
            typeLines.push_back(string("typedef ") + get_type(tokens.at(1)) + " " + name + ";");
        }
    }
    else if(stmtName == "def")
    {
        mvStatementFlag = false;
        string funcName = tokens.at(1);
        if(funcName == "main")
        {
            outline += "void _stodin_main(){";
            funcLines.push_back("\nextern void _stodin_main();");
        }
        else
        {
            outline += "void " + funcName + "(";
            if(staticDef)
            {
                outline = "static " + outline;
            }
            else
            {
                funcLines.push_back("\nextern void " + funcName + "(");
            }
            waitCvStatement = true;
        }
    }
    else if(stmtName == "if")
    {
        outline += do_if_stmt_routine(tokens);
    }
    else if(stmtName == "ifnot")
    {
        outline += do_if_stmt_routine(tokens, true);
    }
    else if(stmtName == "elif")
    {
        outline += "else " + do_if_stmt_routine(tokens);
    }
    else if(stmtName == "else")
    {
        outline += "else{";
    }

    else if(stmtName == "for")
    {
        outline += do_for_stmt_routine(tokens);
    }

    else if((stmtName == "continue") || (stmtName == "break"))
    {
        outline += stmtName + ";";
    }
    else if(stmtName == "cref")
    {
        outline += make_cv_def_line(tokens, "{");
        if(!staticDef)
            funcLines.push_back(make_cv_def_line(tokens, ";"));
        waitCvStatement = false;
    }
    else if(stmtName == "mref")
    {
        outline += make_mv_def_line(tokens);
        if(!staticDef)
            funcLines.push_back(make_mv_def_line(tokens));
        mvStatementFlag = true;
    }

    else if(stmtName == "return")
    {
        outline += stmtName + ";";
    }
    else if(stmtName == "struct")
    {
        inStruct = true;
        if(staticDef)
            outline += stmtName + " " + tokens.at(1) + "{public:";
        else
            typeLines.push_back(stmtName + " " + tokens.at(1) + "{public:");
    }
    else if (stmtName == "try")
    {
        outline += "try{";
    }
    else if (stmtName == "catch")
    {
        outline += "catch(" + tokens.at(1) + "& " + tokens.at(2) + "){";
        if(traceFlag)
        {
            outline += "if(__stodinTrace.size())__stodinTrace.pop_back();";
        }

    }
    else if (stmtName == "throw")
    {
        outline += "throw " + tokens.at(1) + "(" + tokens.at(2) + ");";
    }
    else if (stmtName == "assert")
    {
        string assertMessage = string("#Assert! ") + parser_error::get_line_number() + ", line: "+ parser_error::get_module() + " - ";
        for(auto t : tokens)
            assertMessage += t + " ";
        if(traceFlag)
        {
            outline += "__stodinTrace.push_back(\"" + assertMessage + "\"); throw logic_error(\"-\");";
        }
        else
        {
            outline += do_if_stmt_routine(tokens) + "}else{throw logic_error(\"" +
                assertMessage + "\");}";
        }
    }
    else if ((tokens.size() > 0) && (tokens.at(0) != "."))
    {
        parser_error::add("unknown statement");
        for(auto t : tokens)
            cout << t << " | ";
        cout << endl;
    }

    return outline;
}

void stmt_clear()
{
    funcLines.clear();
    typeLines.clear();
}

};
