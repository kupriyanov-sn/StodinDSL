#include "__stodin_io.h"
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef _WIN32
static const unsigned int __DEFAULT_CONSOLE_CODEPAGE = GetConsoleCP();

// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr, unsigned int codepage)
{
    if( wstr.empty() ) return std::string();
    int size_needed = WideCharToMultiByte(codepage, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo( size_needed, 0 );
    WideCharToMultiByte                  (codepage, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

// Convert an UTF8 string to a wide Unicode String
std::wstring utf8_decode(const std::string &str, unsigned int codepage)
{
    if( str.empty() ) return std::wstring();
    int size_needed = MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

static bool _is_not_ascii(string & src)
{
    for(auto ch : src)
    {
        if(ch & 0x80)
            return true;
    }
    return false;
}

static bool _is_not_ascii(const char * src)
{
    const char * p = src;
    while(p++)
    {
        if((*p) & 0x80)
            return true;
    }
    return false;
}
#endif // _WIN32

string encode_out(string & src)
{
#ifdef _WIN32
    if(_is_not_ascii(src))
        return utf8_encode(utf8_decode(src, CP_UTF8), __DEFAULT_CONSOLE_CODEPAGE);
#endif // _WIN32
    return src;
}

string encode_in(string & src)
{
#ifdef _WIN32
    if(_is_not_ascii(src))
        return utf8_encode(utf8_decode(src, __DEFAULT_CONSOLE_CODEPAGE), CP_UTF8);
#endif // _WIN32
    return src;
}

void print(const char* value)
{
#ifdef _WIN32
    if(_is_not_ascii(value))
    {
        string s = string(value);
        cout << encode_out(s);
    }
    else
#endif // _WIN32
        cout << value;
}

void print(__stodin_string & value)
{
#ifdef _WIN32
    auto s = value.get_string();
    if(_is_not_ascii(s))
    {
        cout << encode_out(s);
    }
    else
#endif // _WIN32
        cout << value;
}

void scan(__stodin_string & value)
{
    string s = "";
    if(!(cin >> s))
    {
        std::cin.clear(istream::goodbit);
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
#ifdef _WIN32
        if(_is_not_ascii(s))
            value = encode_in(s);
        else
#endif // _WIN32
            value = s;
    }
}

void scan(bool & flag, __stodin_string & value)
{
    string s = "";
    if(!(cin >> s))
    {
        std::cin.clear(istream::goodbit);
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        flag = false;
    }
    else
    {
        flag = true;
#ifdef _WIN32
        if(_is_not_ascii(s))
            value = encode_in(s);
        else
#endif // _WIN32
            value = s;
    }
}



void getch(__stodin_string & value)
{
    char ch = '\n';
    cin.get(ch);
    value = __stodin_string(ch);
}

void getch()
{
    char ch = '\n';
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get(ch);
}
