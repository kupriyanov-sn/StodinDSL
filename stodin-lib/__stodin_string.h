#ifndef __STODIN_STRING_H
#define __STODIN_STRING_H
#include <string>
#include <iostream>
#include <functional>

using namespace std;

class __stodin_string
{
    public:
        __stodin_string();
        __stodin_string(const __stodin_string & s);
        __stodin_string(const string & s);
        __stodin_string(const char * s);
        __stodin_string(char ch);
        __stodin_string(char ch, int64_t n);

        __stodin_string& operator= (const __stodin_string& str);
        __stodin_string& operator= (const string& str);
        __stodin_string& operator= (const char* s);
        __stodin_string& operator= (char ch);

        __stodin_string& operator+=(const __stodin_string & s);
        __stodin_string& operator+=(const string & s);
        __stodin_string& operator+=(const char * s);
        __stodin_string& operator+=(char ch);

        friend bool operator== (const __stodin_string& lhs, const __stodin_string& rhs) noexcept;
        friend bool operator== (const __stodin_string& lhs, const string& rhs) noexcept;
        friend bool operator== (const string& lhs, const __stodin_string& rhs) noexcept;
        friend bool operator== (const char*   lhs, const __stodin_string& rhs);
        friend bool operator== (const __stodin_string& lhs, const char*   rhs);
        friend bool operator== (char lhs, const __stodin_string& rhs);
        friend bool operator== (const __stodin_string& lhs, char rhs);

        friend ostream& operator<<(ostream& os, const __stodin_string& str);
        friend istream& operator>> (istream& is, __stodin_string& str);

        friend void getline (__stodin_string& str, char delim);
        friend void getline (__stodin_string& str);
        friend void getline (__stodin_string& str, char delim, bool flag);
        friend void getline (__stodin_string& str, bool flag);

        friend void size(int64_t & sz, const __stodin_string & str);
        friend void empty(bool &res, const __stodin_string& str) noexcept;
        friend void clear(__stodin_string & str);

        friend void insert (__stodin_string& destStr, int64_t pos, const string& sourceStr);
        friend void insert (__stodin_string& destStr, int64_t pos, const __stodin_string& sourceStr);
        friend void insert(__stodin_string& destStr, int64_t pos, const char* sourceStr);
        friend void insert(__stodin_string& destStr, int64_t pos, char ch, int64_t n);
        friend void insert(__stodin_string& destStr, int64_t pos, char ch);

        friend void erase (__stodin_string& str, int64_t pos = 0, int64_t len = string::npos);

        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const string& part);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const string& part,
                         int64_t subpos, int64_t sublen = string::npos);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const __stodin_string& part);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const __stodin_string& part,
                         int64_t subpos, int64_t sublen = string::npos);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const char* s);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const char* s, int64_t n);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, int64_t n, char c);

        friend void find (int64_t & pos, const __stodin_string& str, const string& part, int64_t startPos = 0) noexcept;
        friend void find (int64_t & pos, const __stodin_string& str, const __stodin_string& part, int64_t startPos = 0) noexcept;
        friend void find (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos = 0);
        friend void find (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos, int64_t n);
        friend void find (int64_t & pos, const __stodin_string& str, char c, int64_t startPos = 0) noexcept;

        friend void rfind (int64_t & pos, const __stodin_string& str, const string& part, int64_t startPos = string::npos) noexcept;
        friend void rfind (int64_t & pos, const __stodin_string& str, const __stodin_string& part, int64_t startPos = string::npos) noexcept;
        friend void rfind (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos = string::npos);
        friend void rfind (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos, int64_t n);
        friend void rfind (int64_t & pos, const __stodin_string& str, char c, int64_t startPos = string::npos) noexcept;

        friend void substr (__stodin_string& destStr, const __stodin_string& srcStr,  size_t pos = 0, size_t len = string::npos);
        friend void substr (__stodin_string& destStr, const char* cStr,  size_t pos = 0, size_t len = string::npos);

        friend void to_string (__stodin_string & res, const int val);
        friend void to_string (__stodin_string & res, const long val);
        friend void to_string (__stodin_string & res, const long long val);
        friend void to_string (__stodin_string & res, const unsigned int val);
        friend void to_string (__stodin_string & res, const unsigned long val);
        friend void to_string (__stodin_string & res, const unsigned long long val);
        friend void to_string (__stodin_string & res, const float val);
        friend void to_string (__stodin_string & res, const double val);
        friend void to_string (__stodin_string & res, const long double val);

        friend void from_string(int & res, const __stodin_string & val);
        friend void from_string(long & res, const __stodin_string & val);
        friend void from_string(long long & res, const __stodin_string & val);
        friend void from_string(unsigned int & res, const __stodin_string & val);
        friend void from_string(unsigned long  & res, const __stodin_string & val);
        friend void from_string(unsigned long long & res, const __stodin_string & val);
        friend void from_string(float & res, const __stodin_string & val);
        friend void from_string(double & res, const __stodin_string & val);
        friend void from_string(long double & res, const __stodin_string & val);

        friend void isalnum(bool & res, const __stodin_string str);
        friend void isalpha(bool & res, const __stodin_string str);
        friend void isblank(bool & res, const __stodin_string str);
        friend void iscntrl(bool & res, const __stodin_string str);
        friend void isdigit(bool & res, const __stodin_string str);
        friend void isgraph(bool & res, const __stodin_string str);
        friend void islower(bool & res, const __stodin_string str);
        friend void isprint(bool & res, const __stodin_string str);
        friend void ispunct(bool & res, const __stodin_string str);
        friend void isspace(bool & res, const __stodin_string str);
        friend void isupper(bool & res, const __stodin_string str);
        friend void isxdigit(bool & res, const __stodin_string str);

        friend void toupper(__stodin_string & str);
        friend void tolower(__stodin_string & str);

        char& at(int64_t idx);
        char at(int64_t idx) const;
        char& creating_at(int64_t idx);
        char& creating_at();
        string::iterator begin();
        string::const_iterator begin() const;
        string::iterator end();
        string::const_iterator end() const;

        const string get_string() const;

        virtual ~__stodin_string();
    protected:

    private:
        string _str;
};

namespace std
{
    template<> struct less<__stodin_string>
    {
       bool operator() (const __stodin_string& lhs, const __stodin_string& rhs) const
       {
           return lhs.get_string() < rhs.get_string();
       }
    };
};

// http://www.cplusplus.com/reference/string/string/operators/ - for operators: <, >, >=, <=
bool operator!= (const __stodin_string& lhs, const __stodin_string& rhs) noexcept;
bool operator!= (const __stodin_string& lhs, const string& rhs) noexcept;
bool operator!= (const string& lhs, const __stodin_string& rhs) noexcept;
bool operator!= (const char*   lhs, const __stodin_string& rhs);
bool operator!= (const __stodin_string& lhs, const char*   rhs);
bool operator!= (char lhs, const __stodin_string& rhs);
bool operator!= (const __stodin_string& lhs, char rhs);

// is something
extern void isalnum(bool & res, const char ch);
extern void isalpha(bool & res, const char ch);
extern void isblank(bool & res, const char ch);
extern void iscntrl(bool & res, const char ch);
extern void isdigit(bool & res, const char ch);
extern void isgraph(bool & res, const char ch);
extern void islower(bool & res, const char ch);
extern void isprint(bool & res, const char ch);
extern void ispunct(bool & res, const char ch);
extern void isspace(bool & res, const char ch);
extern void isupper(bool & res, const char ch);
extern void isxdigit(bool & res, const char ch);

extern void toupper(char & ch);
extern void tolower(char & ch);

#endif // __STODIN_STRING_H
