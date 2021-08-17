#pragma once

#include "mdcore/utils.h"

template<class T>
bool errorCheck(std::vector<T> v)
{
    for(auto ele : v)
    {
        if(ele == nullptr)
        {
            return true;
        }
    }
    return false;
}