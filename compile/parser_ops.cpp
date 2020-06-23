#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>


#include "parser_ops.h"

namespace parser
{

const vector<string> mathOperators = {"+", "-", "*", "/", "%", "|", "&", "^", "~", "<<", ">>"};
const vector<string> compareOperators = {"==", "!=", ">", "<", ">=", "<="};
const vector<string> boolOperators = {"&&", "||"};
const string equateOperator = "=";
const string notOperator = "!";
const string sizeOfOperator = "@sizeof"; // ???

static vector<string> allOperators;
static void init_all_operators_vector()
{
    if(allOperators.empty())
    {
        allOperators.insert(allOperators.end(), mathOperators.begin(), mathOperators.end());
        allOperators.insert(allOperators.end(), compareOperators.begin(), compareOperators.end());
        allOperators.insert(allOperators.end(), boolOperators.begin(), boolOperators.end());
        allOperators.push_back(equateOperator);
        allOperators.push_back(notOperator);
        allOperators.push_back(sizeOfOperator);
    }
}

bool is_operator(string & token)
{
    init_all_operators_vector();
    return (std::find(allOperators.begin(), allOperators.end(), token) != allOperators.end());
}

bool is_func(string & token)
{
    return token.at(0) == '@';
}

bool is_func_or_operator(string & token)
{
    return is_func(token) || is_operator(token);
}

}
