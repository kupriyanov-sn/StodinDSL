#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "parser_check.h"
#include "parser_ops.h"
#include "lexer.h"
#include "parser_error.h"

namespace parser
{

map<string, string> types =
{
    {"uint", "uint64_t"}, {"int", "int64_t"}, {"u64", "uint64_t"}, {"i64", "int64_t"},
    {"u8", "uint8_t"}, {"i8", "int8_t"}, {"u16", "uint16_t"}, {"i16", "int16_t"},
    {"u32", "uint32_t"}, {"i32", "int32_t"},
    {"double", "double"}, {"float", "float"}, {"ldouble", "long double"},
    {"string", "__stodin_string"}, {"bool", "__stodin_bool"}, {"array", "__stodin_array"}, {"dict", "__stodin_dict"},
    {"file", "__stodin_file"}
};


bool is_string(string token)
{
    return (token.at(0) == '\"') || (token.at(0) == '\'');
}

string check_enum(string res)
{
    size_t pos = res.find('^');
    if((pos != string::npos) && (pos > 0) && (!is_string(res)) )
    {
        res.replace(pos, 1, "::");
    }
    return res;
}

string check_aggregate(const string op, const bool creating)
{
    if(op == "true")
        return "1";
    if(op == "false")
        return "0";

    string res = "";
    string newType = "";
    string errStr = "";
    vector<string> subtokens;

    lexer::parse_token(op, subtokens, errStr);
    if(errStr.size())
        parser_error::add(string("aggregate error, ") + errStr);
    else
    {
        res = check_module(subtokens[0]);
        for(size_t i = 1; i < subtokens.size(); ++i)
        {
            if(subtokens[i] == "|")
            {
                string index = "";
                if(i + 1 < subtokens.size())
                {
                    if(subtokens[i + 1][0] == '*')
                    {
                        if(subtokens[i + 1].size() > 1)
                            index = subtokens[i + 1].substr(1);
                        else
                            index = "-1";
                        if(creating)
                        {
                            if(index != "-1")
                                res += ".create(" + check_module(index) + ")";
                            else
                                res += ".create()";
                        }
                        else
                            res += ".at(" + check_module(index) + ")";
                    }
                    else if(subtokens[i + 1][0] == '.')
                    {
                        string field = subtokens[i + 1].substr(1);
                        res += "." + check_module(field);
                    }
                    else
                    {
                        index = subtokens[i + 1];
                        res += ".at(" + check_module(index) + ")";
                    }
                }
                ++i;
            }
            else if((subtokens[i] == "$") && (i + 1 != subtokens.size()))
            {
                res = string("static_cast<") + check_common_type(subtokens[i + 1]) + ">(" + res + ")";
                break;
            }
        }
        return check_enum(res);
    }
    return "";
}

string check_module(string op)
{
    if((op.find(':') != string::npos) && (!is_string(op)) )
    {
        size_t pos = op.find(':');
        string moduleName = op.substr(0, pos);
        string funcName = op.substr(pos + 1);
        if(moduleName[0] == '^')
        {
            moduleName = moduleName.substr(1);
            return "_stodin_module_" + moduleName + "::" + funcName;
        }
        else
        {
            return "_stodin_lib_" + moduleName + "::" + funcName;
        }
    }
    else
        return op;
}
string check_common_type(string tStr)
{
    return types.find(tStr) != types.end() ? types[tStr] : check_module(tStr);
}

string get_type(string typeName)
{
    string res = "";
    vector<string> subtokens;
    string errStr = "";
    lexer::parse_token(typeName, subtokens, errStr);
    if(subtokens.size() == 1)
    {
        res = check_common_type(subtokens.at(0));
    }
    else
    {
        size_t counter = 0;
        for(auto st: subtokens)
        {
            if(st == "|")
            {
                res += "<";
                counter++;
            }
            else if(st == ",")
            {
                res += ",";
            }
            else
            {
                res += check_common_type(st);
            }
        }
        for(size_t i = 0; i < counter; ++i)
        {
            res += ">";
        }
    }
    return res;
}

}
