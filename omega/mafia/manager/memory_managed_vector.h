#pragma once

#include <vector>

template<class T>
class MemoryManagedVector
{
    public:
        MemoryManagedVector();
        MemoryManagedVector(T* t){push_back(t)};
        ~MemoryManagedVector();
        std::vector<T> get();
        void push_back(T element)
        {
            //call the copy constructor and get a ptr
            T* element_copy = new (std::nothrow) T(element);
            backend.push_back(element_copy);
        };
        T& operator[](int index)
        {
            return backend[index];
        }
    private:
        std::vector<T> backend;
};