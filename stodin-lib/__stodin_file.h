#ifndef __STODIN_FILE_H
#define __STODIN_FILE_H

#include <fstream>
#include <string>
#include <cstdint>
#include "__stodin_string.h"

using namespace std;

class __stodin_file
{
    public:
        __stodin_file();
        friend void set_mode(__stodin_file & f, const char* mode);
        friend void set_mode(__stodin_file & f, const __stodin_string & mode);
        friend void open(__stodin_file & f, const char* name);
        friend void open(__stodin_file & f, const __stodin_string & name);
        friend void close(__stodin_file & f);

        friend void write(__stodin_file & f, const char * data);
        friend void write(__stodin_file & f, const __stodin_string & data);
        friend void read(__stodin_file & f, __stodin_string &data, const uint64_t n);
        friend void getline(__stodin_string &data, __stodin_file & f);
        friend void getline(__stodin_string &data, __stodin_file & f, const char delim);

        virtual ~__stodin_file();

    protected:
        std::fstream _fs;
        ios_base::openmode _openMode;
    private:
};

#endif // __STODIN_FILE_H
