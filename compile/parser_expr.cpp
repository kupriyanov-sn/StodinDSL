#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>


#include "parser_ops.h"
#include "parser_check.h"
#include "parser_expr.h"
#include "parser_stmt.h"
#include "parser_error.h"

namespace parser
{

bool check_expr(const vector<string> &tokens)
{
    if(tokens.size() && (tokens[0].size()) && (tokens[0][0] == '*')) // constructor
        return true;
    for(size_t i = 0; i < tokens.size(); ++i)
    {
        string s = tokens[i];
        if(is_func(s))
            return true;
        if((i > 0) && (is_operator(s)))
            return true;
    }
    return false;
}

static void get_accums(vector<vector<string> > & accums, bool & constrFlag, vector<string> & tokens, string & initElems)
{
    constrFlag = false;
    initElems = "";
    accums.push_back(vector<string>());
    int counter = 0;
    for(auto s: tokens)
    {
        if(s == ";")
        {
            accums.push_back(vector<string>());
        }
        else if(constrFlag && (is_string(s) || is_int(s) || is_double(s) || is_bool(s)))
        {
            break;
        }
        else if (is_func_or_operator(s) )
        {
            break;
        }
        else
        {
            if(s.at(0) == '*')
            {
                s = s.substr(1);
                constrFlag = true;
            }
            else if(s.find("|*") != string::npos)
            {
                initElems += check_aggregate(s, true) + "; ";
                s = check_aggregate(s);
            }
            else
                s = check_aggregate(s);

            accums.back().push_back(s);
        }
        counter++;
    }
    tokens.erase(tokens.begin(), tokens.begin() + counter);
}

static void get_multi_arg_list(vector<vector<string> > & argsList, const vector<string> & tokens)
{
    argsList.push_back(vector<string>());
    for(size_t i = 1; i < tokens.size(); ++i)
    {
        string arg = tokens.at(i);
        if(arg == ";")
        {
            argsList.push_back(vector<string>());
        }
        else if((arg == "?") || (arg == "!?"))
        {
            argsList.push_back(vector<string>());
            argsList.back().push_back(arg);
        }
        else if(is_func_or_operator(arg))
            break;
        else
        {
            argsList.back().push_back(arg);
        }
    }
}

static string do_func(vector<string> & accums, vector<string> & tokens, string & ifPrep)
{
    string outline = "";
    string funcName = tokens[0].substr(1);
    bool oneConstRef = false;
    if(funcName.back() == '*')
    {
        funcName = funcName.substr(0, funcName.length() - 1);
        oneConstRef = true;
    }
    funcName = check_module(funcName);
    vector<vector<string> > argsList;
    if(oneConstRef)
    {
        for(size_t i = 1; i < tokens.size(); ++i)
        {
            string arg = tokens.at(i);
            if(arg == ";")
            {
                ;
            }
            else if(is_func_or_operator(arg))
                break;
            else
            {
                argsList.push_back(vector<string>());
                argsList.back().push_back(arg);
            }
        }
    }
    else
    {
        get_multi_arg_list(argsList, tokens);
    }
    for(auto args : argsList)
    {
        if(args.size() && args[0] == "?")
        {
            args.erase(args.begin());
            ifPrep = "if(" + accums[0] + "){ ";
        }
        else if(args.size() && args[0] == "!?")
        {
            args.erase(args.begin());
            ifPrep = "if(!" + accums[0] + "){ ";
        }
        outline += ifPrep + funcName + "(";
        for(size_t i = 0; i < accums.size(); ++i)
        {
            outline += accums[i];
            if(args.size() || (i < accums.size() - 1))
                outline += ", ";
        }
        for(size_t i = 0; i < args.size(); ++i)
        {
            outline += check_aggregate(args[i]);
            if(i < args.size() - 1)
                outline += ", ";
        }
        outline += ");";
        if(ifPrep.size()) outline += "}";
    }

    return outline;
}

// {"+", "-", "*", "/", "%", "|", "&", "^", "~", "<<", ">>"};
map<string, string> safeOp =
{
    {"+", "__stodin_plus"}, {"-", "__stodin_minus"}, {"*", "__stodin_mult"}, {"/", "__stodin_div"},
    {"%", "__stodin_rem"}, {"<<", "__stodin_lshift"}
};

static string do_operator(vector<string> & accums, vector<string> & tokens, string & ifPrep, const vector<string> & flags)
{
    string outline = "";
    string accum = accums.at(0);
    string curOper = tokens.at(0);
    bool safeFlag = std::find(flags.begin(), flags.end(), string("-safe")) != flags.end();
    if(curOper == equateOperator)
    {
        if((tokens.size() > 2) && (!is_func_or_operator(tokens.at(2))))
        {
            outline +=  accum + " = {";
            for(size_t i = 1; i < tokens.size(); ++i)
            {
                outline += check_aggregate(tokens[i]);
                if(i != (tokens.size() - 1))
                    outline += ", ";
            }
            outline += "};";
        }
        else
        {
            outline += ifPrep + accum + " = " + check_aggregate(tokens.at(1)) + ";";
            if(ifPrep.size()) outline += "}";
        }
    }
    else if(curOper == notOperator)
    {
        outline += ifPrep + accum + " = !" + check_aggregate(tokens.at(1)) + ";";
        if(ifPrep.size()) outline += "}";
    }
    else if(curOper == sizeOfOperator)
    {
        outline += accum + " = sizeof(" + check_aggregate(tokens.at(1)) + ");";
    }
    else if(std::find(mathOperators.begin(), mathOperators.end(), curOper) != mathOperators.end())
    {
        for(size_t i = 1; i < tokens.size(); ++i)
        {
            if(is_func_or_operator(tokens[i]))
                break;
            else
            {
                if(safeFlag)
                {
                    if(safeOp.find(curOper) != safeOp.end())
                    {
                        outline += safeOp.at(curOper) + "(" + accum + ", " + check_aggregate(tokens[i]) + "); ";
                    }
                    else
                    {
                        outline += accum + " " + curOper + "= " + check_aggregate(tokens[i]) + "; ";
                    }
                }
                else
                {
                    outline += accum + " " + curOper + "= " + check_aggregate(tokens[i]) + "; ";
                }
            }
        }
    }
    else if(std::find(compareOperators.begin(), compareOperators.end(), tokens.at(0)) != compareOperators.end())
    {
        vector<vector<string> > argsList;
        get_multi_arg_list(argsList, tokens);
        for(auto args : argsList)
        {
            if(args.size() && args[0] == "?")
            {
                args.erase(args.begin());
                ifPrep = "if(" + accum + "){ ";
            }
            else if(args.size() && args[0] == "!?")
            {
                args.erase(args.begin());
                ifPrep = "if(!" + accums[0] + "){ ";
            }
            if(args.size() != 2)
                return "#error compare operator";
            else
            {
                outline += ifPrep + accum + " = " + check_aggregate(args[0]) + " " + curOper + " " + check_aggregate(args[1]) + ";";
                if(ifPrep.size()) outline += "}";
            }
        }
    }
    else if(std::find(boolOperators.begin(), boolOperators.end(), tokens.at(0)) != boolOperators.end())
    {
        curOper = tokens[0];
        for(size_t i = 1; i < tokens.size(); ++i)
        {
            if(is_func_or_operator(tokens[i]))
                break;
            else
            {
                outline += ifPrep + check_aggregate(accum) + " = " + check_aggregate(accum)
                           + " " + curOper + " " + check_aggregate(tokens[i]) + "; ";
                if(ifPrep.size()) outline += "}";
            }
        }
    }

    return outline;
}

static void get_if_preposition(string & res, vector<string> & accums)
{
    res = "";
    if(accums.size())
    {
        string accum = accums[0];
        if(accum.back() == '?')
        {
            string neg = "";
            accum = accum.substr(0, accum.size() - 1);
            if(accum.size() && (accum.back() == '!'))
            {
                accum = accum.substr(0, accum.size() - 1);
                neg = "!";
            }
            res = "if(" + neg + accum + "){ ";
            accums[0] = accum;
        }
    }
}

static string do_func_or_operator(vector<string> & accums, string & ifPrep, vector<string> & tokens, const vector<string> & flags)
{
    string outline = "";
    string op = tokens.at(0);

    if(is_operator(op))
    {
        outline = do_operator(accums, tokens, ifPrep, flags);
    }
    else
    {
        outline = do_func(accums, tokens, ifPrep);
    }
    tokens.erase(tokens.begin()); // erase func or operator name
    while(tokens.size() && ( !is_func_or_operator(tokens.front()) ) )
        tokens.erase(tokens.begin());

    return outline;
}

string do_expr_routine(vector<string> &tokens, const vector<string> & flags)
{
    string outline = "";
    vector<vector<string> > accList;
    bool constrFlag = false;
    string initElemsStr;
    get_accums(accList, constrFlag, tokens, initElemsStr);
    for(auto accums: accList)
    {
        string ifPrep = "";
        get_if_preposition(ifPrep, accums);
        vector<string> locTokens = tokens;
        if(constrFlag)
            outline += do_constructor(accums.at(0), locTokens);
        outline += initElemsStr;
        while(locTokens.size())
        {
            string expr = do_func_or_operator(accums, ifPrep, locTokens, flags);
            if(std::find(flags.begin(), flags.end(), string("-trace")) != flags.end())
            {
                expr = "try{" + expr + "}catch(exception & __stodin_ex){__stodinTrace.push_back((string(\"### " + parser_error::get_module() +
                    "\") + \", line: " + parser_error::get_line_number() + ": \" + __stodin_ex.what()).c_str()); throw;}";
            }
            outline += expr;
        }
    }
    return outline;
}

}
