#include <cstring>
#include "__stodin_file.h"

__stodin_file::__stodin_file()
{
    _openMode = ios_base::in;
}

static ios_base::openmode check_mode(char m)
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
        f._openMode = check_mode(s[0]);
    for(size_t i = 1; i < s.size(); ++i)
        f._openMode |= check_mode(s[i]);
}


void set_mode(__stodin_file & f, const char* mode)
{
    __stodin_string sMode = mode;
    set_mode(f, sMode);
}

void open(__stodin_file & f, const char* name)
{
    f._fs.open(name, f._openMode);
}

void open(__stodin_file & f, const __stodin_string & name)
{
    string s = name.get_string();
    f._fs.open(s.c_str(), f._openMode);
}
void close(__stodin_file & f)
{
    f._fs.close();
}

void write(__stodin_file & f, const char * data)
{
    f._fs.write(data, strlen(data));
}

void write(__stodin_file & f, const __stodin_string & data)
{
    f._fs << data;
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
}

void getline(__stodin_string &data, __stodin_file & f)
{
    string str;
    getline(f._fs, str);
    data = str;
}

void getline(__stodin_string &data, __stodin_file & f, const char delim)
{
    string str;
    getline(f._fs, str, delim);
    data = str;
}

__stodin_file::~__stodin_file()
{
    if(_fs.is_open())
        _fs.close();
}
