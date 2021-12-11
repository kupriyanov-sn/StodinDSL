#include <cstring>
#include "__stodin_file.h"

__stodin_file::__stodin_file()
{
    _openMode = ios_base::in;
}

static ios_base::openmode _check_mode(char m)
{
    if(m == 'r')
        return ios_base::in;
    if(m == 'w')
        return ios_base::out;
    if(m == 'a')
        return ios_base::ate;
    if(m == 'p')
        return ios_base::app;
    if(m == 'b')
        return ios_base::binary;
    if(m == 't')
        return ios_base::trunc;
    return ios_base::in;
}

void set_mode(__stodin_file & f, const __stodin_string & mode)
{
    auto s = mode.get_string();
    if(s.size() == 0)
        f._openMode = ios_base::in;
    else
        f._openMode = _check_mode(s[0]);
    for(size_t i = 1; i < s.size(); ++i)
        f._openMode |= _check_mode(s[i]);
}

static void _check_error(const std::fstream& fs, const char* message)
{
    if(!(fs.good() || fs.eof()))
    {
        throw runtime_error(message);
    }
}

void set_mode(__stodin_file & f, const char* mode)
{
    __stodin_string sMode = mode;
    set_mode(f, sMode);
}

void open(__stodin_file & f, const char* name)
{
    f._fs.open(name, f._openMode);
    _check_error(f._fs, "Open file error!");
}

void open(__stodin_file & f, const __stodin_string & name)
{
    string s = name.get_string();
    f._fs.open(s.c_str(), f._openMode);
    _check_error(f._fs, "Open file error!");
}

void close(__stodin_file & f)
{
    f._fs.close();
    _check_error(f._fs, "Close file error!");
}

void write(__stodin_file & f, const char * data)
{
    f._fs.write(data, strlen(data));
    _check_error(f._fs, "File write error!");
}

void write(__stodin_file & f, const __stodin_string & data)
{
    f._fs << data;
    _check_error(f._fs, "File write error!");
}

void read(__stodin_file & f, __stodin_string &data, const uint64_t n)
{
    clear(data);
    for(uint64_t i = 0; i < n; ++i)
    {
        char ch;
        f._fs.get(ch);
        data += ch;
    }
    _check_error(f._fs, "File read error!");
}

void getline(__stodin_string &data, __stodin_file & f)
{
    string str;
    getline(f._fs, str);
    if(str.back() == '\n')
        str.pop_back();
    if(str.back() == '\r')
        str.pop_back();
    data = str;
    _check_error(f._fs, "File getline error!");
}

void getline(__stodin_string &data, __stodin_file & f, const char delim)
{
    string str;
    getline(f._fs, str, delim);
    data = str;
    _check_error(f._fs, "File getline error!");
}

void getlines(__stodin_array<__stodin_string> &data, __stodin_file & f)
{
    string str;
    while(getline(f._fs, str))
    {
        if(str.back() == '\n')
            str.pop_back();
        if(str.back() == '\r')
            str.pop_back();
        add(data, str);
    }    
}

void get_state_string(__stodin_string &res, const __stodin_file & f)
{
    if(f._fs.good())
        res = "good";
    else if(f._fs.eof())
        res = "eof";
    else if(f._fs.fail())
        res = "fail";
    else if(f._fs.bad())
        res = "bad";
}

void clear_errors(__stodin_file & f)
{
    f._fs.clear();
}

__stodin_file::~__stodin_file()
{
    if(_fs.is_open())
        _fs.close();
}
