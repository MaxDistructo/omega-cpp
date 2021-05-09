#pragma once

#include <vector>
#include <algorithm>

template<class T>
bool vectorContains(std::vector<T> v, T t)
{
    return std::count(v.begin(), v.end(), t);
}

template<class T>
typename std::vector<T>::iterator getIterLocation(std::vector<T> v, T t)
{
    for(typename std::vector<T>::iterator iter; iter < v.end(); iter++)
    {
        if(*iter == t)
        {
            return iter;
        }
    }
    return v.end();
}

template<class T>
int getIndex(std::vector<T> v, T t)
{
    for(size_t i = 0; i < v.size(); i++)
    {
        if(v[i] == t)
        {
            return i;
        }
    }
    return -1;
}