// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector

#include "vector.h"

template<typename T>
Vector<T>::Vector()
{
    v_size = 0;
}

template<typename T>
Vector<T>::Vector(uint64_t nv_size)
{
    v_size = nv_size;
    if(v_size > 0)
        v_data = new T[v_size];
}

template<typename T>
uint64_t
Vector<T>::size()
{
    return v_size;
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
Vector<T>::~Vector()
{
    if(v_size > 0)
        delete[] v_data;
}


template class Vector<int>;
