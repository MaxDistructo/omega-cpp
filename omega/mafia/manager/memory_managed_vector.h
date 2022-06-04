#pragma once

#include <vector>

template<class T>
class MemoryManagedVector
{
    public:
        MemoryManagedVector();
        MemoryManagedVector(std::initializer_list<T> l)
        {
            for(T ele : l)
            {
                push_back(ele);
            }
        }
        MemoryManagedVector(std::initializer_list<T*> l)
        {
            for(T* ele : l)
            {
                backend.push_back(ele);
            }
        }
        ~MemoryManagedVector()
        {
            for(T* ele : backend)
            {
                delete ele;
            }
        };
        struct Iterator
        {
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T*;
            Iterator()
            {
                #ifndef __clang__
                m_ptr = get(index);
                #endif
            }
            Iterator(pointer ptr) : m_ptr(ptr) {};
            private:
                pointer m_ptr;
                int index = 0;
                void increment()
                {
                    index++;
                    #ifndef __clang__
                    m_ptr = get(index);
                    #endif
                }
            public:
                reference operator*() const {return m_ptr; }
                pointer operator->() { return m_ptr; }
                Iterator& operator++() 
                {
                    increment();
                    return *this;
                };
                Iterator operator++(int) 
                {
                    //Store copy of self
                    Iterator tmp = *this;
                    //Increment
                    increment();
                    //Return the copy
                    return tmp;
                };

                friend bool operator== (const Iterator& a, const Iterator& b) 
                {
                    return a.m_ptr == b.m_ptr;
                }

                friend bool operator!= (const Iterator& a, const Iterator& b)
                {
                    return a.m_ptr != b.m_ptr;
                }
        };
        Iterator begin() {return Iterator();};
        Iterator end() {return Iterator(&backend[backend.size() + 1]);};
        const std::vector<T*> getBackend()
        {
            return backend; 
        };
        T* get(int index)
        {
            return backend[index];
        }
        void push_back(T& element)
        {
            //call the copy constructor and get a ptr
            T* element_copy = new (std::nothrow) T(element);
            backend.push_back(element_copy);
        };
        void push_back(T* element)
        {
            //call the copy constructor and get a ptr
            T* element_copy = new (std::nothrow) T(element);
            backend.push_back(element_copy);
        };
        size_t size()
        {
            return backend.size();
        };
        T* operator[](int index)
        {
            return get(index);
        };


    private:
        std::vector<T*> backend;
};