#include "__stodin_common.h"

vector<string> __stodinTrace;
static vector<string> __stodinArgs;

ostream& operator<<(ostream& os, const exception& ex)
{
    os << ex.what();
    return os;
}

void _stodin_parse_args(int argc, char** argv)
{
    for(int i = 0; i < argc; ++i)
    {
        __stodinArgs.push_back(argv[0]);
    }
}

void get_application_arg(__stodin_string & res, int64_t idx)
{
    if(static_cast<size_t>(idx) < __stodinArgs.size())
        res = __stodinArgs[idx];
    else
        res = "";
}

void get_all_application_args(__stodin_array<__stodin_string> & res)
{
    clear(res);
    for(auto s: __stodinArgs)
        add(res, s);
}
