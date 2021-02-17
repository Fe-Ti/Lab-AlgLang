// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector

#include "vector.h"

template<typename T>
Vector<T>::Vector()
{
    v_size = 0;
    v_alloc_size = 0;
    v_data = nullptr;
}

template<typename T>
Vector<T>::Vector(uint64_t nv_size)
{
    v_size = nv_size;
    v_alloc_size = v_size;
    if(v_alloc_size > 0) {
        v_data = new T[v_alloc_size];
        for(uint64_t i = 0; i < v_size; ++i) {
            v_data[i] = 0;
        }
    } else {
        v_data = nullptr;
    }
}

template<typename T>
Vector<T>::Vector(Vector& vec)
{
    v_size = vec.v_size;
    v_alloc_size = v_size; // creating a copy only of defined elements
    if(v_alloc_size > 0) {
        v_data = new T[v_alloc_size];
        for(uint64_t i = 0; i < v_size; ++i) {
            v_data[i] = vec.v_data[i];
        }
    } else {
        v_data = nullptr;
    }
}

template<typename T>
uint64_t
Vector<T>::size()
{
    return v_size;
}

template<typename T>
uint64_t
Vector<T>::allocated_size()
{
    return v_alloc_size;
}

template<typename T>
T*
Vector<T>::data()
{
    return v_data;
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
    if(v_alloc_size == v_size) {
        if(v_alloc_size != 0)
            v_alloc_size *= 2;
        else
            ++v_alloc_size;
        T* new_v_data = new T[v_alloc_size];
        for(uint64_t i = 0; i < v_size; ++i) {
            new_v_data[i] = v_data[i];
        }
        delete[] v_data;
        v_data = new_v_data;
    }
    v_data[v_size] = node;
    ++v_size;
}

template<typename T>
uint64_t
Vector<T>::find(T node)
{
    for(uint64_t i = 0; i < v_size; ++i) {
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
    for(uint64_t i = 0; i < v_size; ++i) {
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
