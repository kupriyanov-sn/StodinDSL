#ifndef __STODIN_ARRAY_H
#define __STODIN_ARRAY_H
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <stdexcept>      // std::out_of_range
#include "__stodin_types.h"

using namespace std;

template <typename T>
class __stodin_array
{

    public:
        __stodin_array()
        {
        }

        __stodin_array(std::initializer_list<T> lst)
        {
            _array = vector<T>(lst);
        }

        T& at(int64_t idx)
        {
            if(idx > -1)
                return _array.at(static_cast<size_t>(idx));
            else
                return _array.at(static_cast<size_t>(_array.size() + idx));
        }

        T at(int64_t idx) const
        {
            if(idx > -1)
                return _array.at(static_cast<size_t>(idx));
            else
                return _array.at(static_cast<size_t>(_array.size() + idx));
        }

        void create(int64_t idx)
        {
            size_t newSize = static_cast<size_t>(idx + 1);
            if(_array.size() != newSize)
                _array.resize(newSize);
        }

        void create()
        {
            create(_array.size());
        }

        friend void add(__stodin_array<T>& arr, const T &elem)
        {
            arr._array.push_back(elem);
        }

        friend void add(__stodin_array<T>& arr)
        {
            arr._array.resize(arr._array.size() + 1);
        }

        friend void resize(__stodin_array<T>& arr, int64_t sz)
        {
            arr._array.resize(sz);
        }

        friend void resize(__stodin_array<T>& arr, int64_t sz, const T value)
        {
            size_t prev_sz = arr._array.size();
            arr._array.resize(sz);
            if(sz > static_cast<int64_t>(prev_sz))
                fill(arr._array.begin() + prev_sz, arr._array.end(), value);
        }

        friend void fill(__stodin_array<T>& arr, const T value)
        {
            fill(arr._array.begin(), arr._array.end(), value);
        }

        friend void fill(__stodin_array<T>& arr, const int64_t begin, const int64_t end, const T value)
        {
            if((begin < 0) || (end < 1) || (begin >= end) || (end > static_cast<int64_t>(arr._array.size())))
                throw std::out_of_range("Array index out of bounds!");
            fill(arr._array.begin() + begin, arr._array.begin() + end, value);
        }

        friend void copy_elem(T &elem, const __stodin_array<T>& arr, int64_t idx)
        {
            if(idx > -1)
                elem = arr._array.at(idx);
            else
                elem = arr._array.at(arr._array.size() + idx);
        }

        friend void erase(__stodin_array<T>& arr, int64_t idx)
        {
            if(idx > -1)
                arr._array.erase(arr._array.begin() + static_cast<size_t>(idx));
            else
                arr._array.erase(arr._array.begin() + static_cast<size_t>(arr._array.size() + idx));
        }

        friend void clear(__stodin_array<T>& arr)
        {
            arr._array.clear();
        }
        friend void size(int64_t & sz, const __stodin_array<T>& arr)
        {
            sz = arr._array.size();
        }

        friend void find(int64_t& pos, const __stodin_array<T>& arr, const T& value)
        {
            auto res = std::find(arr._array.begin(), arr._array.end(), value);
            if(res != arr._array.end())
                pos = res - arr._array.begin();
            else
                pos = -1;
        }

        // "for each" methods
        typedef typename vector<T>::iterator iter;
        typedef typename vector<T>::const_iterator c_iter;
        iter begin()
        {
            return _array.begin();
        }
        iter end()
        {
            return _array.end();
        }
        c_iter begin() const
        {
            return _array.cbegin();
        }
        c_iter end() const
        {
            return _array.cend();
        }
    protected:

    private:
        vector<T> _array;
};

#endif // __STODIN_ARRAY_H
