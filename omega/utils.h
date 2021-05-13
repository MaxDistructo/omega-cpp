#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include "mafia/player.h"

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

template<class T>
std::string toString(std::vector<T> v, std::string seperator)
{
    std::string out;
    for(size_t i = 0; i < v.size(); i++)
    {
        if(i != (v.size() - 1))
        {
            out += v[i] + seperator;
        }
        else {
            out += v[i];
        }
    }
    return out;
}

template<class T>
std::string toString(std::vector<T> v)
{
    return toString(v, ", ");
}