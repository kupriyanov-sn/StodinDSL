#ifndef _STODIN_LIB_FILEINFO_H
#define _STODIN_LIB_FILEINFO_H

#include "__stodin_string.h"
#include "__stodin_array.h"

namespace _stodin_lib_fileinfo
{
    extern void file_exists(bool & res, const char * name);
    extern void file_exists(bool & res, __stodin_string & name);
    extern void get_last_modification_time(int64_t & res, const char * filename);
    extern void create_folder(const char * path);
    extern void create_folder(__stodin_string & path);
    extern void join(__stodin_string & res, __stodin_string & dirName, __stodin_string & fileName);
    extern void join(__stodin_string & res, __stodin_string & dirName, const char * fileName);
    extern void join(__stodin_string & res, const char * dirName, __stodin_string & fileName);
    extern void join(__stodin_string & dirName, __stodin_string & fileName);
    extern void join(__stodin_string & dirName, const char * fileName);
    extern void compare_files(bool & res, const __stodin_string & file1, const __stodin_string & file2);
    extern void compare_files(bool & res, const __stodin_string & file1, const char * file2);
    extern void compare_files(bool & res, const char * file1, const __stodin_string & file2);
    extern void compare_files(bool & res, const char * file1, const char * file2);
    extern void copy_file(const __stodin_string & from, const __stodin_string & to);
    extern void copy_file(const __stodin_string & from, const char * to);
    extern void copy_file(const char * from, const __stodin_string & to);
    extern void copy_file(const char * from, const char * to);
    extern void get_dir(__stodin_string & res, const __stodin_string & filePath);
    extern void get_dir(__stodin_string & res, const char * filePath);
    extern void get_file_name(__stodin_string & res, const __stodin_string & path);

}

#endif // _STODIN_LIB_FILEINFO_H
