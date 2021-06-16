// Copyright 2021 Fe-Ti <btm.007@mail.ru>
#include <iostream>

#ifndef VECTOR
#define VECTOR

/*
 * This is a vector imitation, which does not copy STL very accurate
 * Implementation can:
 *  - be used in range based for;
 *  - push and pop back the values;
 *  -
 *
 *
 *
 *
 *
 *
 *
 */

#include <cmath>
#include <stdexcept>

#include "rao_iterator.hpp"

template<typename T>
class Vector
{
    T* _data;
    size_t _size;
    size_t _alloc_size;

    float magnifier = 1.5;

    void copy_data_to(T* new_data,
                      size_t csize,
                      size_t ref_offset = 0,
                      size_t copy_offset = 0)
    {
        for (size_t i = 0; i < csize; ++i) {
            new_data[i + copy_offset] = _data[i + ref_offset];
        }
    }

  public:
    Vector()
    {
        _data = nullptr;
        _size = 0;
        _alloc_size = 0;
    }

    Vector(const size_t& size, float custom_magnifier = 1.5)
    {
        magnifier = custom_magnifier;
        _alloc_size = size;
        _data = new T[size];
    }

    Vector(const Vector& origin_v, float custom_magnifier = 1.5)
    {
        magnifier = custom_magnifier;
        _alloc_size = std::round(origin_v.size() * magnifier);
        _data = new T[_alloc_size];
        _size = origin_v.size();
        origin_v.copy_data_to(_data, _size);
    }

    T& at(const size_t& index)
    {
        if (index > size())
            throw std::out_of_range();
        return _data[index];
    }

    T& operator[](const size_t& index) { return _data[index]; }

    T& front() { return _data[0]; }

    T& back() { return _data[_size - 1]; }

    T* data() { return _data; }

    size_t size() const { return _size; }

    size_t capacity() const { return _alloc_size - 1; }

    size_t allocated_size() const { return _alloc_size; }

    RAO_iterator<T> begin() { return RAO_iterator<T>(&_data[0]); }

    RAO_iterator<T> end() { return RAO_iterator<T>(&_data[_size]); }

    bool empty() { return _size == 0; }

    void reserve(size_t new_size)
    {
        if (new_size > capacity()) {
            T* new_data = new T[new_size + 1];
            // we are speaking about capacity
            // so we need one more element in the array
            copy_data_to(new_data, _size);
            delete[] _data;
            _data = new_data;
            _alloc_size = new_size + 1;
            _size = new_size;
        }
    }

    void push_back(T element)
    {
        if (_alloc_size == 0) {
            // if there are no elements then one does not simply multiply
            _alloc_size = std::round(magnifier);
            _data = new T[_alloc_size];
            _data[0] = element;
            ++_size;
        } else if (_size == capacity()) {
            // if there isn't enough space then get some more
            _alloc_size = std::round(_alloc_size * magnifier);
            T* new_data = new T[_alloc_size];
            copy_data_to(new_data, _size);
            delete[] _data;
            _data = new_data;
            _data[_size] = element;
            ++_size;
        } else {
            // else just append the element
            _data[_size] = element;
            ++_size;
        }
    }

    void shrink_to_fit()
    {
        if (_size == capacity()) {
            return;
        }
        _alloc_size = _size + 1;
        T* new_data = new T[_alloc_size];
        copy_data_to(new_data, _size);
        delete[] _data;
        _data = new_data;
    }

    void insert(size_t index, const T& element, size_t el_count = 1)
    {
        if (index < _size) {
            if (_size + el_count - 1 < capacity()) {
                for (size_t i = _size - 1; i >= index; --i) {
                    _data[i + el_count] = _data[i];
                }
            } else {
                _alloc_size = std::round((_alloc_size + el_count) * magnifier);
                T* new_data = new T[_alloc_size];
                copy_data_to(new_data, index);
                copy_data_to(new_data, _size - index, index, index + el_count);
                delete[] _data;
                _data = new_data;
            }
            for (size_t i = index; i < index + el_count; ++i) {
                _data[i] = element;
            }
            _size += el_count;
        } else {
            throw std::out_of_range("Index is out of vector");
        }
    }

    void erase(RAO_iterator<T> iter) {}
    void erase(RAO_iterator<T> iter_first, RAO_iterator<T> iter_last) {}

    void pop_back()
    {
        if (_size != 0) {
            --_size; // just say we have one element less
        }
    }

    void resize(size_t new_size)
    /*
     * if new size is equal to _size then do nothing
     * else if _alloc_size is enough
     *     then just say 'OK, its _size is now bigger|lesser'
     *     else alloc more space
     * This behavior is somewhat different comparing to STL
     */
    {
        if (new_size == _size)
            return;
        if (new_size >= _alloc_size) {
            T* new_data = new T[new_size + 1];
            copy_data_to(new_data, _size);
            delete[] _data;
            _data = new_data;
            _alloc_size = new_size + 1;
        }
        _size = new_size;
    }

    void clear()
    {
        delete[] _data;
        _data = nullptr;
        _size = 0;
        _alloc_size = 0;
    }

    ~Vector() { delete[] _data; }

    Vector<T>& operator=(Vector& vec)
    {
        if (_data != nullptr)
            delete[] _data;
        _size = vec._size;
        _alloc_size = _size; // creating a copy only of defined elements
        if (_alloc_size > 0) {
            _data = new T[_alloc_size];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = vec._data[i];
            }
        } else {
            _data = nullptr;
        }
        return *this;
    }
    template<typename TF>
    friend void swap(Vector<TF>& v0, Vector<TF>& v1);
};

template<typename TF>
void
swap(Vector<TF>& v0, Vector<TF>& v1)
{
    TF* tmp = v0._data;
    v0._data = v1._data;
    v1._data = tmp;
}

#endif
