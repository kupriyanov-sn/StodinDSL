#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <string>
#include <vector>
using namespace std;
namespace lexer
{
    bool get_tokens(string inputString, vector<string> &tokens, size_t &indents, string &errorStr);
    void parse_token(const string inputString, vector<string> &tokens, string &errorStr);
}
#endif // LEXER_H_INCLUDED
