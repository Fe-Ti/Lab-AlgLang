// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector (size via ptr tp the last)

#include "vector.h"

template<typename T>
Vector<T>::Vector()
{
    v_alloc_size = 0;
    v_data = nullptr;
    v_end = nullptr;
}

template<typename T>
Vector<T>::Vector(uint64_t nv_size)
{
}

template<typename T>
T*
Vector<T>::end() const
{
    return v_end;
}

template<typename T>
T*
Vector<T>::data() const
{
    return v_data;
}

template<typename T>
uint64_t
Vector<T>::size() const
{
    return v_end - v_data;
}

template<typename T>
uint64_t
Vector<T>::allocated_size() const
{
    return v_alloc_size;
}

template<typename T>
Vector<T>::Vector(Vector& vec)
{
}

template<typename T>
T& Vector<T>::operator[](const uint64_t index)
{
    return v_data[index];
}

template<typename T>
void
Vector<T>::push_back(T node)
{
}

template<typename T>
uint64_t
Vector<T>::find(T node) const
{
    for(uint64_t i = 0; i < size(); ++i) {
        if(v_data[i] == node)
            return i;
    }
    return -1;
}

template<typename T>
void
Vector<T>::replace(T node0, T node1, uint64_t count)
{
    if(node0 == node1)
        return;
    for(uint64_t i = 0; i < size(); ++i) {
        if(count < 1)
            break;
        if(v_data[i] == node0) {
            v_data[i] = node1;
            --count;
        }
    }
}
template<typename T>
void
Vector<T>::replace(T node0, T node1) // overload for the fnc above
{
    replace(node0, node1, 1);
}

template<typename T>
Vector<T>::~Vector()
{
    delete[] v_data;
}

template class Vector<int>;
