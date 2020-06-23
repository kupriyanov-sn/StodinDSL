#ifndef __STODIN_IO_H
#define __STODIN_IO_H

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <limits>
#include "__stodin_string.h"

using namespace std;

void print(const char* value);
void print(__stodin_string & value);

template <typename T>
void print(const T & value)
{
    cout << value;
}


template <typename T>
void scan(T & value)
{
    if(!(cin >> value))
    {
        std::cin.clear(istream::goodbit);
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void scan(__stodin_string & value);
void scan(bool & flag, __stodin_string & value);

template <typename T>
void scan(bool & flag, T & value)
{
    if(!(cin >> value))
    {
        std::cin.clear(istream::goodbit);
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        flag = false;
    }
    else flag = true; // commented for saving error
}


extern void getch(__stodin_string & value);
extern void getch();



#endif // __STODIN_IO_H
