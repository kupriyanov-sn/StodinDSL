#include <limits>
#include <cstdlib>
#include <cctype>
#include "__stodin_string.h"

/// constructors
__stodin_string::__stodin_string()
{
    _str = "";
}

__stodin_string::__stodin_string(const __stodin_string & s)
{
    _str = s._str;
}

__stodin_string::__stodin_string(const string & s)
{
    _str = s;
}

__stodin_string::__stodin_string(const char * s)
{
    _str = s;
}

__stodin_string::__stodin_string(char ch)
{
    _str = string(1, ch);
}

__stodin_string::__stodin_string(char ch, int64_t n)
{
    _str = string(static_cast<size_t>(n), ch);
}

/// operator=

__stodin_string& __stodin_string::operator= (const __stodin_string& str)
{
    _str = str._str;
    return *this;
}

__stodin_string& __stodin_string::operator= (const string& str)
{
    _str = str;
    return *this;
}

__stodin_string& __stodin_string::operator= (const char* s)
{
    _str = s;
    return *this;
}

__stodin_string& __stodin_string::operator= (char ch)
{
    _str = string(1, ch);
    return *this;
}

/// append operator

__stodin_string& __stodin_string::operator+=(const __stodin_string& s)
{
    _str += s._str;
    return *this;
}

__stodin_string& __stodin_string::operator+=(const string& s)
{
    _str += s;
    return *this;
}

__stodin_string& __stodin_string::operator+=(const char * s)
{
    _str += s;
    return *this;
}

__stodin_string& __stodin_string::operator+=(char ch)
{
    _str += ch;
    return *this;
}

/// compare operator ==

__stodin_bool operator== (const __stodin_string& lhs, const __stodin_string& rhs) noexcept
{
    return lhs._str == rhs._str;
}

__stodin_bool operator== (const __stodin_string& lhs, const string& rhs) noexcept
{
    return lhs._str == rhs;
}

__stodin_bool operator== (const string& lhs, const __stodin_string& rhs) noexcept
{
    return lhs == rhs._str;
}

__stodin_bool operator== (const char*   lhs, const __stodin_string& rhs)
{
    return rhs._str == lhs;
}

__stodin_bool operator== (const __stodin_string& lhs, const char*   rhs)
{
    return lhs._str == rhs;
}

__stodin_bool operator== (char lhs, const __stodin_string& rhs)
{
    return (rhs._str.size() == 1) && (rhs._str[0] == lhs);
}

__stodin_bool operator== (const __stodin_string& lhs, char rhs)
{
    return (lhs._str.size() == 1) && (lhs._str[0] == rhs);
}

/// compare operator !=

__stodin_bool operator!= (const __stodin_string& lhs, const __stodin_string& rhs) noexcept
{
    return !(lhs == rhs);
}
__stodin_bool operator!= (const __stodin_string& lhs, const string& rhs) noexcept
{
    return !(lhs == rhs);
}
__stodin_bool operator!= (const string& lhs, const __stodin_string& rhs) noexcept
{
    return !(lhs == rhs);
}
__stodin_bool operator!= (const char*   lhs, const __stodin_string& rhs)
{
    return !(lhs == rhs);
}
__stodin_bool operator!= (const __stodin_string& lhs, const char*   rhs)
{
    return !(lhs == rhs);
}
__stodin_bool operator!= (char lhs, const __stodin_string& rhs)
{
    return !(lhs == rhs);
}
__stodin_bool operator!= (const __stodin_string& lhs, char rhs)
{
    return !(lhs == rhs);
}

/// stream operators

ostream& operator<<(ostream& os, const __stodin_string& str)
{
    os << str._str;
    return os;
}

istream& operator>> (istream& is, __stodin_string& str)
{
    is >> str._str;
    return is;
}

void getline (__stodin_string& str, char delim)
{
    getline(cin, str._str, delim);
}

void getline ( __stodin_string& str)
{
    getline(cin, str._str);
}

void getline (__stodin_string& str, char delim, __stodin_bool flag)
{
    getline(cin, str._str, delim);
    if(!cin)
    {
        cin.clear(istream::goodbit);
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        flag = true;
    }
}

void getline (__stodin_string& str, __stodin_bool flag)
{
    getline(cin, str._str);
    if(!cin)
    {
        cin.clear(istream::goodbit);
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        flag = true;
    }
}


/// various functions
void size(int64_t & sz, const __stodin_string & str)
{
    sz = str._str.size();
}

void utf8_size(int64_t & sz, const __stodin_string & str)
{
    sz = 0;
    for(auto ch: str._str)
    {
        uint8_t code = static_cast<uint8_t>(ch) & 0xC0;
        if(code != 0x80)
            sz++;
    }
}

void empty(__stodin_bool &res, const __stodin_string& str) noexcept
{
    res = str._str.empty();
}
void clear(__stodin_string & str)
{
    str._str.clear();
}

void insert (__stodin_string& destStr, int64_t pos, const string& sourceStr)
{
    destStr._str.insert(pos, sourceStr);
}

void insert (__stodin_string& destStr, int64_t pos, const __stodin_string& sourceStr)
{
    destStr._str.insert(pos, sourceStr._str);
}

void insert(__stodin_string& destStr, int64_t pos, const char* sourceStr)
{
    destStr._str.insert(pos, sourceStr);
}

void insert(__stodin_string& destStr, int64_t pos, char ch, int64_t n)
{
    destStr._str.insert(pos, ch, n);
}

void insert(__stodin_string& destStr, int64_t pos, char ch)
{
    destStr._str.insert(pos, ch, 1);
}

void erase (__stodin_string& str, int64_t pos, int64_t len)
{
    str._str.erase(pos, len);
}

void replace (__stodin_string& str, int64_t pos, int64_t len, const string& part)
{
    str._str.replace(pos, len, part);
}
void replace (__stodin_string& str, int64_t pos, int64_t len, const string& part,
          int64_t subpos, int64_t sublen)
{
    str._str.replace(pos, len, part, subpos, sublen);
}
void replace (__stodin_string& str, int64_t pos, int64_t len, const __stodin_string& part)
{
    str._str.replace(pos, len, part._str);
}
void replace (__stodin_string& str, int64_t pos, int64_t len, const __stodin_string& part,
          int64_t subpos, int64_t sublen)
{
    str._str.replace(pos, len, part._str, subpos, sublen);
}
void replace (__stodin_string& str, int64_t pos, int64_t len, const char* part)
{
    str._str.replace(pos, len, part);
}
void replace (__stodin_string& str, int64_t pos, int64_t len, const char* part, int64_t n)
{
    str._str.replace(pos, len, part, n);
}
void replace (__stodin_string& str, int64_t pos, int64_t len, int64_t n, char c)
{
    str._str.replace(pos, len, n, c);
}

void find (int64_t & pos, const __stodin_string& str, const string& part, int64_t startPos) noexcept
{
    size_t sPos = str._str.find(part, startPos);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}
void find (int64_t & pos, const __stodin_string& str, const __stodin_string& part, int64_t startPos) noexcept
{
    size_t sPos = str._str.find(part._str, startPos);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}
void find (int64_t & pos, const __stodin_string& str, const char* part, int64_t startPos)
{
    size_t sPos = str._str.find(part, startPos);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}
void find (int64_t & pos, const __stodin_string& str, const char* part, int64_t startPos, int64_t n)
{
    size_t sPos = str._str.find(part, startPos, n);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}
void find (int64_t & pos, const __stodin_string& str, char c, int64_t startPos) noexcept
{
    size_t sPos = str._str.find(c, startPos);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}

void rfind (int64_t & pos, const __stodin_string& str, const string& part, int64_t startPos) noexcept
{
    size_t sPos = str._str.rfind(part, startPos);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}
void rfind (int64_t & pos, const __stodin_string& str, const __stodin_string& part, int64_t startPos) noexcept
{
    size_t sPos = str._str.rfind(part._str, startPos);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}
void rfind (int64_t & pos, const __stodin_string& str, const char* part, int64_t startPos)
{
    size_t sPos = str._str.rfind(part, startPos);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}
void rfind (int64_t & pos, const __stodin_string& str, const char* part, int64_t startPos, int64_t n)
{
    size_t sPos = str._str.rfind(part, startPos, n);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}
void rfind (int64_t & pos, const __stodin_string& str, char c, int64_t startPos) noexcept
{
    size_t sPos = str._str.rfind(c, startPos);
    pos = sPos != string::npos ? static_cast<int64_t>(sPos) : -1;
}

void substr (__stodin_string& destStr, const __stodin_string& srcStr,  size_t pos, size_t len)
{
    destStr._str = srcStr._str.substr(pos, len);
}

void substr (__stodin_string& destStr, const char* cStr,  size_t pos, size_t len)
{
    string srcStr = string(cStr);
    destStr._str = srcStr.substr(pos, len);
}

/// to string

void to_string (__stodin_string & res, const int val)
{
    res._str = std::to_string(val);
}
void to_string (__stodin_string & res, const long val)
{
    res._str = std::to_string(val);
}
void to_string (__stodin_string & res, const long long val)
{
    res._str = std::to_string(val);
}
void to_string (__stodin_string & res, const unsigned int val)
{
    res._str = std::to_string(val);
}
void to_string (__stodin_string & res, const unsigned long val)
{
    res._str = std::to_string(val);
}
void to_string (__stodin_string & res, const unsigned long long val)
{
    res._str = std::to_string(val);
}
void to_string (__stodin_string & res, const float val)
{
    res._str = std::to_string(val);
}
void to_string (__stodin_string & res, const double val)
{
    res._str = std::to_string(val);
}
void to_string (__stodin_string & res, const long double val)
{
    res._str = std::to_string(val);
}

/// from string

void from_string(int & res, const __stodin_string & val)
{
    res = stoi(val._str);
}
void from_string(long & res, const __stodin_string & val)
{
    res = stol(val._str);
}
void from_string(long long & res, const __stodin_string & val)
{
    res = stoll(val._str);
}
void from_string(unsigned int & res, const __stodin_string & val)
{
    res = static_cast<unsigned int>(stoul(val._str));
}
void from_string(unsigned long  & res, const __stodin_string & val)
{
    res = stoul(val._str);
}
void from_string(unsigned long long & res, const __stodin_string & val)
{
    res = stoull(val._str);
}
void from_string(float & res, const __stodin_string & val)
{
    res = stof(val._str);
}
void from_string(double & res, const __stodin_string & val)
{
    res = stod(val._str);
}
void from_string(long double & res, const __stodin_string & val)
{
    res = stold(val._str);
}

/// at and iterators

char& __stodin_string::at(int64_t idx)
{
    if(idx > -1)
        return _str.at(static_cast<size_t>(idx));
    else
        return _str.at(static_cast<size_t>(_str.size() + idx));
}

char __stodin_string::at(int64_t idx) const
{
    if(idx > -1)
        return _str.at(static_cast<size_t>(idx));
    else
        return _str.at(static_cast<size_t>(_str.size() + idx));
}

char& __stodin_string::creating_at(int64_t idx)
{
    size_t newSize = static_cast<size_t>(idx + 1);
    if(_str.size() != newSize)
        _str.resize(newSize);
    return _str[idx];
}

char& __stodin_string::creating_at()
{
    return creating_at(_str.size());
}

string::iterator __stodin_string::begin()
{
    return _str.begin();
}

string::const_iterator __stodin_string::begin() const
{
    return _str.begin();
}
string::iterator __stodin_string::end()
{
    return _str.end();
}
string::const_iterator __stodin_string::end() const
{
    return _str.end();
}

const string __stodin_string::get_string() const
{
    return _str;
}

__stodin_string::~__stodin_string()
{
    //dtor
}

// string is something

void isalnum(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isalnum(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void isalpha(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isalpha(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void isblank(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isblank(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void iscntrl(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        iscntrl(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void isdigit(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isdigit(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void isgraph(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isgraph(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void islower(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        islower(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void isprint(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isprint(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void ispunct(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        ispunct(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void isspace(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isspace(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void isupper(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isupper(b, ch);
        res = res && b;
        if(!res) break;
    }
}
void isxdigit(__stodin_bool & res, const __stodin_string str)
{
    res = !(str._str.empty());
    for(auto & ch: str._str)
    {
        __stodin_bool b = false;
        isxdigit(b, ch);
        res = res && b;
        if(!res) break;
    }
}

void toupper(__stodin_string & str)
{
    for(auto & ch: str) toupper(ch);
}
void tolower(__stodin_string & str)
{
    for(auto & ch: str) tolower(ch);
}

// ch is something
void isalnum(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isalnum(static_cast<int>(ch)));
}
void isalpha(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isalpha(static_cast<int>(ch)));
}
void isblank(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isblank(static_cast<int>(ch)));
}
void iscntrl(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(iscntrl(static_cast<int>(ch)));
}
void isdigit(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isdigit(static_cast<int>(ch)));
}
void isgraph(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isgraph(static_cast<int>(ch)));
}
void islower(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(islower(static_cast<int>(ch)));
}
void isprint(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isprint(static_cast<int>(ch))) || (ch > 127);
}
void ispunct(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(ispunct(static_cast<int>(ch))) || (ch > 127);
}
void isspace(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isspace(static_cast<int>(ch)));
}
void isupper(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isupper(static_cast<int>(ch)));
}
void isxdigit(__stodin_bool & res, const char ch)
{
    res = static_cast<__stodin_bool>(isxdigit(static_cast<int>(ch)));
}

void toupper(char & ch)
{
    ch = static_cast<char>(toupper(static_cast<int>(ch)));
}
void tolower(char & ch)
{
    ch = static_cast<char>(tolower(static_cast<int>(ch)));
}
