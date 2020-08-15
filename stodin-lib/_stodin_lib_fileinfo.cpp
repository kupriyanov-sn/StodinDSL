#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>
#include <iterator>

#include <sys/stat.h>
#ifndef _WIN32
#include <unistd.h>
#endif //_WIN32

#ifdef _WIN32
#include <windows.h>
#define stat _stat
#endif //_WIN32

#include "_stodin_lib_fileinfo.h"

namespace _stodin_lib_fileinfo
{
    void file_exists(__stodin_bool & res, const char * name)
    {
        struct stat buffer;
        res = (stat(name, &buffer) == 0);
    }

    void file_exists(__stodin_bool & res, __stodin_string & name)
    {
        file_exists(res, name.get_string().c_str());
    }

    void get_last_modification_time(int64_t & res, const char * filename)
    {
        struct stat result;
        if(stat(filename, &result) != 0)
            res = 0;
        else
            res = static_cast<int64_t>(result.st_mtime);
    }

    void create_folder(const char * path)
    {
#ifdef _WIN32
        if(!CreateDirectory(path, nullptr))
        {
            return;
        }
#else
        mkdir(path, S_IRWXU);
#endif //_WIN32
    }

    void create_folder(__stodin_string & path)
    {
        create_folder(path.get_string().c_str());
    }

    void join(__stodin_string & res, __stodin_string & dirName, __stodin_string & fileName)
    {
#ifdef _WIN32
        char slash = '\\';
#else
        char slash = '/';
#endif // _WIN32
        if(dirName.at(-1) == slash)
        {
            res = dirName; res += fileName;
        }
        else
        {
            res = dirName; res += slash; res += fileName;
        }
    }

    void join(__stodin_string & res, __stodin_string & dirName, const char * fileName)
    {
        __stodin_string s = fileName;
        join(res, dirName, s);
    }

    void join(__stodin_string & res, const char * dirName, __stodin_string & fileName)
    {
        __stodin_string s = dirName;
        join(res, s, fileName);
    }

    void join(__stodin_string & dirName, __stodin_string & fileName)
    {
        __stodin_string s = dirName;
        join(dirName, s, fileName);
    }

    void join(__stodin_string & dirName, const char * fileName)
    {
        __stodin_string s = dirName;
        join(dirName, s, fileName);
    }

    static __stodin_bool _compare_files(const std::string& file1, const std::string& file2)
    { // https://stackoverflow.com/questions/6163611/compare-two-files
        std::ifstream f1(file1, ios::binary);
        std::ifstream f2(file2, ios::binary);

        if (f1.tellg() != f2.tellg())
        {
            return false; //size mismatch
        }

        //seek back to beginning and use std::equal to compare contents
        f1.seekg(0, std::ifstream::beg);
        f2.seekg(0, std::ifstream::beg);
        return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                        std::istreambuf_iterator<char>(),
                        std::istreambuf_iterator<char>(f2.rdbuf()));
    }

    void compare_files(__stodin_bool & res, const __stodin_string & file1, const __stodin_string & file2)
    {
        res = _compare_files(file1.get_string(), file2.get_string());
    }

    void compare_files(__stodin_bool & res, const __stodin_string & file1, const char * file2)
    {
        res = _compare_files(file1.get_string(), string(file2));
    }

    void compare_files(__stodin_bool & res, const char * file1, const __stodin_string & file2)
    {
        res = _compare_files(string(file1), file2.get_string());
    }

    void compare_files(__stodin_bool & res, const char * file1, const char * file2)
    {
        res = _compare_files(string(file1), string(file2));
    }

    void copy_file(const __stodin_string & from, const __stodin_string & to)
    {
        string from_ = from.get_string();
        string to_ = to.get_string();
        if(!_compare_files(from_, to_))
        {
            ifstream source(from_, ios::binary);
            ofstream dest(to_, ios::binary);

            dest << source.rdbuf();

            source.close();
            dest.close();
        }
    }

    void copy_file(const __stodin_string & from, const char * to)
    {
        copy_file(from, __stodin_string(to));
    }

    void copy_file(const char * from, const __stodin_string & to)
    {
        copy_file(__stodin_string(from), to);
    }

    void copy_file(const char * from, const char * to)
    {
        copy_file(__stodin_string(from), __stodin_string(to));
    }

    void get_dir(__stodin_string & res, const __stodin_string & filePath)
    {
        string filePath_ =  filePath.get_string();
        size_t pos = filePath_.rfind('\\');
        if(pos == string::npos) pos = filePath_.rfind('/');
        if(pos != string::npos)
            res = filePath_.substr(0, pos + 1);
        else
            res = "";
    }

    void get_dir(__stodin_string & res, const char * filePath)
    {
        get_dir(res, __stodin_string(filePath));
    }

    void get_file_name(__stodin_string & res, const __stodin_string & path)
    {
        string path_ = path.get_string();
        size_t pos = path_.rfind('\\');
        if(pos == string::npos) pos = path_.rfind('/');
        string shortName = path_;
        if(pos != string::npos)
            shortName = path_.substr(pos + 1);
        pos = shortName.rfind('.');
        if(pos != string::npos)
            shortName = shortName.substr(0, pos);
        res = shortName;
    }

    void get_file_name(__stodin_string & res, const char * path)
    {
        get_file_name(res, __stodin_string(path));
    }
}
