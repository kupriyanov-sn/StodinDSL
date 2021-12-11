#ifndef __STODIN_DICT_H
#define __STODIN_DICT_H
#include <map>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include "__stodin_types.h"
#include "__stodin_string.h"

using namespace std;

template <typename TKey, typename TValue>
class __stodin_dict
{

    public:
        __stodin_dict()
        {
        }

        __stodin_dict(std::initializer_list<pair<TKey const, TValue>> lst)
        {
            _dict = map<TKey, TValue>(lst);
        }

        TValue& at(const char * idx)
        {
            __stodin_string sidx = idx;
            return _dict.at(sidx);
        }

        TValue& at(const TKey idx)
        {
            return _dict.at(idx);
        }

        TValue at(const char * idx) const
        {
            __stodin_string sidx = idx;
            return _dict.at(sidx);
        }

        TValue at(const TKey idx) const
        {
            return _dict.at(idx);
        }

        void create(const char * idx)
        {
            __stodin_string sidx = idx;
            _dict[sidx];
        }

        void create(const TKey idx)
        {
            _dict[idx];
        }


        friend void add(__stodin_dict<TKey, TValue>& dict, const TKey & key, const TValue & value)
        {
            dict._dict.insert(std::pair<TKey, TValue>(key, value));
        }


        friend void clear(__stodin_dict<TKey, TValue>& dict)
        {
            dict._dict.clear();
        }

        friend void size(int64_t & sz, const __stodin_dict<TKey, TValue>& dict)
        {
            sz = dict._dict.size();
        }

        friend void find(__stodin_dict<TKey, TValue>& dict, pair<TKey, TValue> & keyValue, __stodin_bool & exist, const TKey & key)
        {
            pair<TKey, TValue> res = dict._dict.find(key);
            exist = (res != dict._dict.end());
            if(exist)
                keyValue = res;
        }

        friend void has_key(__stodin_bool & exist, const __stodin_dict<TKey, TValue>& dict, const TKey & key)
        {
            exist = (dict._dict.find(key) != dict._dict.end());
        }

        // "for each" methods
        typedef typename map<TKey, TValue>::iterator iter;
        typedef typename map<TKey, TValue>::const_iterator c_iter;
        iter begin()
        {
            return _dict.begin();
        }
        iter end()
        {
            return _dict.end();
        }
        c_iter begin() const
        {
            return _dict.cbegin();
        }
        c_iter end() const
        {
            return _dict.cend();
        }
    protected:

    private:
        map<TKey, TValue> _dict;
};

#endif // __STODIN_DICT_H
