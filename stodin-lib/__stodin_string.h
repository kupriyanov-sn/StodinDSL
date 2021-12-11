#ifndef __STODIN_STRING_H
#define __STODIN_STRING_H
#include <string>
#include <iostream>
#include <functional>
#include "__stodin_types.h"

using namespace std;

class __stodin_string;

extern void erase (__stodin_string& str, int64_t pos = 0, int64_t len = string::npos);
extern void replace (__stodin_string& str, int64_t pos, int64_t len, const string& part,
          int64_t subpos, int64_t sublen = string::npos);
extern void replace (__stodin_string& str, int64_t pos, int64_t len, const __stodin_string& part,
          int64_t subpos, int64_t sublen = string::npos);
extern void find (int64_t & pos, const __stodin_string& str, const string& part, int64_t startPos = 0) noexcept;
extern void find (int64_t & pos, const __stodin_string& str, const __stodin_string& part, int64_t startPos = 0) noexcept;
extern void find (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos = 0);
extern void find (int64_t & pos, const __stodin_string& str, char c, int64_t startPos = 0) noexcept;

extern void rfind (int64_t & pos, const __stodin_string& str, const string& part, int64_t startPos = string::npos) noexcept;
extern void rfind (int64_t & pos, const __stodin_string& str, const __stodin_string& part, int64_t startPos = string::npos) noexcept;
extern void rfind (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos = string::npos);
extern void rfind (int64_t & pos, const __stodin_string& str, char c, int64_t startPos = string::npos) noexcept;

extern void substr (__stodin_string& destStr, const __stodin_string& srcStr,  size_t pos = 0, size_t len = string::npos);
extern void substr (__stodin_string& destStr, const char* cStr,  size_t pos = 0, size_t len = string::npos);

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

        friend __stodin_bool operator== (const __stodin_string& lhs, const __stodin_string& rhs) noexcept;
        friend __stodin_bool operator== (const __stodin_string& lhs, const string& rhs) noexcept;
        friend __stodin_bool operator== (const string& lhs, const __stodin_string& rhs) noexcept;
        friend __stodin_bool operator== (const char*   lhs, const __stodin_string& rhs);
        friend __stodin_bool operator== (const __stodin_string& lhs, const char*   rhs);
        friend __stodin_bool operator== (char lhs, const __stodin_string& rhs);
        friend __stodin_bool operator== (const __stodin_string& lhs, char rhs);

        friend ostream& operator<<(ostream& os, const __stodin_string& str);
        friend istream& operator>> (istream& is, __stodin_string& str);

        friend void getline (__stodin_string& str, char delim);
        friend void getline (__stodin_string& str);
        friend void getline (__stodin_string& str, char delim, __stodin_bool flag);
        friend void getline (__stodin_string& str, __stodin_bool flag);

        friend void size(int64_t & sz, const __stodin_string & str);
        friend void utf8_size(int64_t & sz, const __stodin_string & str);
        friend void empty(__stodin_bool &res, const __stodin_string& str) noexcept;
        friend void clear(__stodin_string & str);

        friend void insert (__stodin_string& destStr, int64_t pos, const string& sourceStr);
        friend void insert (__stodin_string& destStr, int64_t pos, const __stodin_string& sourceStr);
        friend void insert(__stodin_string& destStr, int64_t pos, const char* sourceStr);
        friend void insert(__stodin_string& destStr, int64_t pos, char ch, int64_t n);
        friend void insert(__stodin_string& destStr, int64_t pos, char ch);

        friend void erase (__stodin_string& str, int64_t pos, int64_t len);

        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const string& part);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const string& part,
                         int64_t subpos, int64_t sublen);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const __stodin_string& part);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const __stodin_string& part,
                         int64_t subpos, int64_t sublen);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const char* s);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, const char* s, int64_t n);
        friend void replace (__stodin_string& str, int64_t pos, int64_t len, int64_t n, char c);

        friend void find (int64_t & pos, const __stodin_string& str, const string& part, int64_t startPos) noexcept;
        friend void find (int64_t & pos, const __stodin_string& str, const __stodin_string& part, int64_t startPos) noexcept;
        friend void find (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos);
        friend void find (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos, int64_t n);
        friend void find (int64_t & pos, const __stodin_string& str, char c, int64_t startPos) noexcept;

        friend void rfind (int64_t & pos, const __stodin_string& str, const string& part, int64_t startPos) noexcept;
        friend void rfind (int64_t & pos, const __stodin_string& str, const __stodin_string& part, int64_t startPos) noexcept;
        friend void rfind (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos);
        friend void rfind (int64_t & pos, const __stodin_string& str, const char* s, int64_t startPos, int64_t n);
        friend void rfind (int64_t & pos, const __stodin_string& str, char c, int64_t startPos) noexcept;

        friend void substr (__stodin_string& destStr, const __stodin_string& srcStr,  size_t pos, size_t len);
        friend void substr (__stodin_string& destStr, const char* cStr,  size_t pos, size_t len);

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

        friend void isalnum(__stodin_bool & res, const __stodin_string str);
        friend void isalpha(__stodin_bool & res, const __stodin_string str);
        friend void isblank(__stodin_bool & res, const __stodin_string str);
        friend void iscntrl(__stodin_bool & res, const __stodin_string str);
        friend void isdigit(__stodin_bool & res, const __stodin_string str);
        friend void isgraph(__stodin_bool & res, const __stodin_string str);
        friend void islower(__stodin_bool & res, const __stodin_string str);
        friend void isprint(__stodin_bool & res, const __stodin_string str);
        friend void ispunct(__stodin_bool & res, const __stodin_string str);
        friend void isspace(__stodin_bool & res, const __stodin_string str);
        friend void isupper(__stodin_bool & res, const __stodin_string str);
        friend void isxdigit(__stodin_bool & res, const __stodin_string str);

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
       __stodin_bool operator() (const __stodin_string& lhs, const __stodin_string& rhs) const
       {
           return lhs.get_string() < rhs.get_string();
       }
    };
};

// http://www.cplusplus.com/reference/string/string/operators/ - for operators: <, >, >=, <=
__stodin_bool operator!= (const __stodin_string& lhs, const __stodin_string& rhs) noexcept;
__stodin_bool operator!= (const __stodin_string& lhs, const string& rhs) noexcept;
__stodin_bool operator!= (const string& lhs, const __stodin_string& rhs) noexcept;
__stodin_bool operator!= (const char*   lhs, const __stodin_string& rhs);
__stodin_bool operator!= (const __stodin_string& lhs, const char*   rhs);
__stodin_bool operator!= (char lhs, const __stodin_string& rhs);
__stodin_bool operator!= (const __stodin_string& lhs, char rhs);

// is something
extern void isalnum(__stodin_bool & res, const char ch);
extern void isalpha(__stodin_bool & res, const char ch);
extern void isblank(__stodin_bool & res, const char ch);
extern void iscntrl(__stodin_bool & res, const char ch);
extern void isdigit(__stodin_bool & res, const char ch);
extern void isgraph(__stodin_bool & res, const char ch);
extern void islower(__stodin_bool & res, const char ch);
extern void isprint(__stodin_bool & res, const char ch);
extern void ispunct(__stodin_bool & res, const char ch);
extern void isspace(__stodin_bool & res, const char ch);
extern void isupper(__stodin_bool & res, const char ch);
extern void isxdigit(__stodin_bool & res, const char ch);

extern void toupper(char & ch);
extern void tolower(char & ch);

#endif // __STODIN_STRING_H
