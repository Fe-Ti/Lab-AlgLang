// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector

#include "vector.hpp"

template<typename T> Vector<T>::Vector() noexcept
{
    v_size = 0;
    v_alloc_size = 0;
    v_data = nullptr;
}

template<typename T> Vector<T>::Vector(uint64_t nv_size) noexcept
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

template<typename T> Vector<T>::Vector(const Vector& vec) noexcept
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
Vector<T>&
Vector<T>::operator=(Vector&& vec) noexcept
{
    if(v_data != nullptr)
        delete[] v_data;
    v_size = vec.v_size;
    v_alloc_size = v_size;
    v_data = vec.data();
    vec.v_data = nullptr;
    return *this;
}

template<typename T>
Vector<T>&
Vector<T>::operator=(Vector& vec) noexcept
{
    if(v_data != nullptr)
        delete[] v_data;
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
    return *this;
}

template<typename T>
uint64_t
Vector<T>::size() const noexcept
{
    return v_size;
}

template<typename T>
uint64_t
Vector<T>::capacity() const noexcept
{
    return v_alloc_size;
}

template<typename T>
T*
Vector<T>::data() noexcept
{
    return v_data;
}

template<typename T>
bool
Vector<T>::empty() const noexcept
{
    return v_size == 0;
}

template<typename T>
T&
Vector<T>::operator[](const uint64_t index)
{
    return v_data[index];
}

template<typename T>
T&
Vector<T>::at(const uint64_t index)
{
    if(index < v_size) {
        return v_data[index];
    } else {
        throw std::out_of_range;
    }
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

template<typename T> Vector<T>::~Vector() noexcept
{
    delete[] v_data;
}

template class Vector<int>;
