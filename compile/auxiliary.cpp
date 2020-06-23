#include <sys/stat.h>
#ifndef _WIN32
#include <unistd.h>
#endif //_WIN32

#ifdef _WIN32
#include <windows.h>
#define stat _stat
#endif //_WIN32
#include "auxiliary.h"

namespace auxiliary
{

    bool file_exists(const std::string& name)
    {
      struct stat buffer;
      return (stat (name.c_str(), &buffer) == 0);
    }

    time_t get_last_modification_time(string filename)
    {
        struct stat result;
        if(stat(filename.c_str(), &result) != 0)
        {
            return 0;
        }
        return result.st_mtime;
    }

    void cpp11_create_folder(string & path)
    {
#ifdef _WIN32
        if(!CreateDirectory(path.c_str(), nullptr))
        {
            return;
        }
#else
        mkdir(path.c_str(), S_IRWXU);
#endif //_WIN32
    }

    string join(string dirName, string fileName)
    {
#ifdef _WIN32
        char slash = '\\';
#else
        char slash = '/';
#endif // _WIN32
        if(dirName.size())
        {
            if(dirName.at(dirName.size() - 1) == slash)
            {
                return dirName + fileName;
            }
            else
            {
                return dirName + slash + fileName;
            }
        }
        return fileName;
    }

    bool compare_files(const std::string& file1, const std::string& file2)
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

    void cpp11_copy_file(string from, string to)
    {
        if(!compare_files(from, to))
        {
            ifstream source(from, ios::binary);
            ofstream dest(to, ios::binary);

            dest << source.rdbuf();

            source.close();
            dest.close();
        }
    }

    string get_dir(string filePath)
    {
        size_t pos = filePath.rfind('\\');
        if(pos == string::npos) pos = filePath.rfind('/');
        if(pos != string::npos)
            return filePath.substr(0, pos + 1);
        else
            return "";
    }

    string get_file_name(string path)
    {
        size_t pos = path.rfind('\\');
        if(pos == string::npos) pos = path.rfind('/');
        string shortName = path;
        if(pos != string::npos)
            shortName = path.substr(pos + 1);
        pos = shortName.rfind('.');
        if(pos != string::npos)
            shortName = shortName.substr(0, pos);
        return shortName;
    }

};
