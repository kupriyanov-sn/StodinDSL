#include <sstream>
#include <algorithm>
#include <iostream>

#include "lexer.h"

using namespace std;

namespace lexer
{

static const string ignoreChars = "(){}[]";

string & check_char(string &token)
{
    if(token.size() == 3)
    {
        if((token[0] == '\"') && (token[2] == '\"'))
            token = string("\'") + token[1] + "\'";
    }
    else if(token.size() == 4)
    {
        if((token[0] == '\"') && (token[1] == '\\') && (token[3] == '\"'))
            token = string("\'\\") + token[2] + "\'";
    }
    return token;
}

bool get_tokens(string inputString, vector<string> &tokens, size_t &indents, string &errorStr)
{
    //cout << "lexer: " << inputString << endl;
    tokens = vector<string>();
    string token = "";
    indents = 0;
    errorStr = "";
    size_t spaces = 0;
    size_t quotes = 0;
    for(size_t i = 0; i < inputString.length(); ++i)
    {
        if(inputString[i] == ' ')
            spaces ++;
        else
            break;
    }
    if(spaces % 4 == 0)
        indents = spaces / 4;
    else
    {
        errorStr = "Error! Wrong space quantity! (" + inputString + ")";
        return false;
    }
    inputString += ' ';

    for(size_t i = 0; i < inputString.length(); ++i)
    {
        char c = inputString[i];
        if((c == '\r') || (c == '\n'))
            continue;
        if(c == '#')
        {
            if(token.length())
            {
                tokens.push_back(check_char(token));
            }
            break;
        }
        else if(c == '\"' )
        {
            int slashCount = 0;
            quotes++;
            if(token.length() && (token.back() == ' '))
            {
                tokens.push_back(check_char(token));
                token = "";
            }
            token += "\"";
            i++;
            while( (!((inputString[i] == '\"') && (slashCount == 0))) && (i < inputString.length()))
            {
                if(inputString[i] == '\\')
                {
                    if(slashCount) slashCount = 0;
                    else slashCount++;
                }
                else
                {
                    slashCount = 0;
                }
                token += inputString[i];
                i++;
            }
            if(inputString[i] == '\"')
            {
                quotes++;
                token += "\"";
            }
        }
        else if(c == ' ')
        {
            if(token.length())
            {
                tokens.push_back(check_char(token));
                token = "";
            }
        }
        else if(c == ';')
        {
            if(token.length())
            {
                tokens.push_back(check_char(token));
            }
            tokens.push_back(";");
            token = "";
        }
        else if(c == '|')
        {
            if(tokens.empty() && token.empty())
            {
                tokens.push_back("|");
            }
            else
                token += c;
        }
        else if(ignoreChars.find(c) !=  string::npos)
        {
            errorStr += "Error char: ";
            errorStr += c;
            return false;
        }
        else
        {
            token += c;
        }
    }
    if(token.size())
    {
        tokens.push_back(check_char(token));
        token = "";
    }

    if(quotes % 2 != 0)
    {
        errorStr = "Error! Quotes number is odd!";
        return false;
    }
    return true;
}

static const string separators = "|$,;";

void parse_token(const string inputString, vector<string> &tokens, string &errorStr)
{
    tokens = vector<string>();
    string token = "";
    errorStr = "";
    size_t quotes = 0;

    for(size_t i = 0; i < inputString.length(); ++i)
    {
        char c = inputString[i];
        if((c == '\"') || (c == '\'') )
        {
            int slashCount = 0;
            quotes++;
            if(token.length() && (token != "*"))
            {
                tokens.push_back(token);
                token = "";
            }
            token += c;
            i++;
            while( (!(((inputString[i] == '\"') || (inputString[i] == '\'')) && (slashCount == 0))) && (i < inputString.length()))
            {
                if(inputString[i] == '\\')
                {
                    if(slashCount) slashCount = 0;
                    else slashCount++;
                }
                else
                {
                    slashCount = 0;
                }
                token += inputString[i];
                i++;
            }
            if((inputString[i] == '\"') || (inputString[i] == '\''))
            {
                quotes++;
                token += inputString[i];
            }
            //tokens.push_back(token);
            //token = "";
        }
        else if(ignoreChars.find(c) !=  string::npos)
        {
            errorStr += "Error char: ";
            errorStr += c;
            break;
        }
        else if( separators.find(c) !=  string::npos)
        {
            if(token.length())
            {
                tokens.push_back(token);
                tokens.push_back(string() + c);
                token = "";
            }
        }
        else
        {
            token += c;
        }
    }
    if(token.size())
    {
        tokens.push_back(token);
    }

    if(quotes % 2 != 0)
    {
        errorStr += "Error! Quotes number is odd!";
    }
}
}
