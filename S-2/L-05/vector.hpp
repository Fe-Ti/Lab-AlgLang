// Copyright 2021 Fe-Ti <btm.007@mail.ru>
#ifndef VECTOR
#define VECTOR

#include <cmath>

//#include "rao_iterator.hpp"

template<typename T>
class Vector
{
    T* _data;
    size_t _size;
    size_t _alloc_size;

    float magnifier = 1.5;

    void copy_data_to(T* new_data, csize = _size)
    {
        for (size_t i = 0; i < csize; ++i) {
            new_data[i] = _data[i];
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
        _data = new T[size];
        _alloc_size = size;
        magnifier = custom_magnifier;
    }

    T& at(const size_t& index)
    {
        if (index > size())
            throw std::out_of_range();
        return _data[index];
    }

    operator[](const size_t& index) { return _data[index]; }

    T& front() { return _data[0]; }

    T& back() { return _data[_size - 1]; }

    T* data() { return _data; }

    size_t size() const { return _size; }

    size_t capacity() const { return _alloc_size - 1; }

    size_t allocated_size() const { return _alloc_size; }

    //RAO_iterator begin() { return RAO_iterator(&_data[0]); }

    //RAO_iterator end() { return RAO_iterator(&_data[_size]); }

    bool empty() { return _size == 0; }

    void reserve(size_t new_size)
    {
        if (new_size > capacity()) {
            new_data = new T[new_size + 1]; // we are speaking about capacity
            copy_data_to(new_data); // so we need one more element in the array
            delete[] _data;
            _data = new_data;
            _alloc_size = new_size + 1;
            _size = new_size;
        }
    }

    void insert(size_t index) {}
    void erase(RAO_iterator iter) {}
    void erase(RAO_iterator iter_first, RAO_iterator iter_last) {}

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
            copy_data_to(new_data);
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
            new_data = new T[new_size + 1];
            copy_data_to(new_data);
            delete[] _data;
            _data = new_data;
            _alloc_size = new_size + 1;
        }
        _size = new_size;
    }

    friend inline void swap(Vector<T>& v0, Vector<T>& v1);

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
            for (uint64_t i = 0; i < _size; ++i) {
                _data[i] = vec._data[i];
            }
        } else {
            _data = nullptr;
        }
        return *this;
    }
};

template<typename T>
void
swap(Vector<T>& v0, Vector<T>& v1)
{
    T* tmp = v0._data;
    v0._data = v1._data;
    v1._data = tmp;
}

#endif
