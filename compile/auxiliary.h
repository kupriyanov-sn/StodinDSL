#ifndef AUXILIARY_H
#define AUXILIARY_H
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>
#include <iterator>


#include <sys/types.h>

using namespace std;

namespace auxiliary
{
    extern bool file_exists(const std::string& name);
    extern time_t get_last_modification_time(string filename);
    extern void cpp11_create_folder(string & path);
    extern string join(string dirName, string fileName);
    extern string get_dir(string filePath);
    extern string get_file_name(string path);
    extern bool compare_files(const std::string& file1, const std::string& file2);
    extern void cpp11_copy_file(string from, string to);
};

#endif // AUXILIARY_H
