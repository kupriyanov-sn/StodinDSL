#include <cctype>
#include "_stodin_lib_exstr.h"

namespace _stodin_lib_exstr
{
    void strip(__stodin_string &res, const __stodin_string &src)
    {
        int64_t beg  {0};
        int64_t end;
        size(end, src);end -= 1;
        for(auto &ch: src)
        {
            if(isspace(ch) || iscntrl(ch))
            {
                beg += 1;
            }
            else
            {
                break;
            }
        }
        for(int64_t i = end; i > 0; i += -1)
        {
            if(isspace(src.at(i)) || iscntrl(src.at(i)))
            {
                end -= 1;
            }
            else
            {
                break;
            }
        }
        end += 1;
        substr(res, src, beg, end);
    }

    void strip(__stodin_string &res)
    {
        __stodin_string s  {res};
        strip(res, s);
    }
}

