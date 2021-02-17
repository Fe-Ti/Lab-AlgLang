// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector (size via ptr tp the last)

#include "vector.h"

template<typename T>
Vector<T>::Vector()
{
    v_alloc_size = 0;
    v_data = nullptr;
    v_back = nullptr;
}

template<typename T>
Vector<T>::Vector(uint64_t nv_size)
{
    v_alloc_size = nv_size;
    if(v_alloc_size != 0) {
        v_data = new T[v_alloc_size];
        v_back = &v_data[v_alloc_size - 1];
    } else {
        v_data = nullptr;
        v_back = nullptr;
    }
}

template<typename T>
Vector<T>::Vector(Vector& vec)
{
    v_alloc_size = vec.size();
    if(v_alloc_size != 0) {
        v_data = new T[v_alloc_size];
        v_back = &v_data[v_alloc_size - 1];
        for(uint64_t i = 0; i < v_alloc_size; ++i) {
            v_data[i] = vec[i];
        }
    } else {
        v_data = nullptr;
        v_back = nullptr;
    }
}

template<typename T>
T*
Vector<T>::back() const
{
    return v_back;
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
    return v_back - v_data + 1;
}

template<typename T>
uint64_t
Vector<T>::allocated_size() const
{
    return v_alloc_size;
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
    if(size() == v_alloc_size) {
        if(v_alloc_size == 0) {
            ++v_alloc_size;
        } else {
            v_alloc_size *= 2;
        }
        T* new_v_data = new T[v_alloc_size];
        for(uint64_t i = 0; i < size(); ++i) {
            new_v_data[i] = v_data[i];
        }
        new_v_data[size()] = node;
        v_back = &new_v_data[size()];
        delete[] v_data;
        v_data = new_v_data;
    } else {
        v_data[size()] = node;
        v_back = &v_data[size()];
    }
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
