#ifndef PARSER_OPS_H
#define PARSER_OPS_H

#include <string>
#include <vector>

using namespace std;


namespace parser
{
extern const vector<string> mathOperators;
extern const vector<string> compareOperators;
extern const vector<string> boolOperators;
extern const string equateOperator;
extern const string notOperator;
extern const string sizeOfOperator;

extern bool is_operator(string & token);
extern bool is_func(string & token);
extern bool is_func_or_operator(string & token);

};

#endif // PARSER_OPS_H
