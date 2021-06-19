// Copyright 2021 Fe-Ti <btm.007@mail.ru>

//#include <iostream>

#ifndef VECTOR
#define VECTOR

/*
 * This vector imitation does not copy STL very accurate.
 *
 * The Implementation can:
 *  - be used in range based for;
 *  - push and pop back the values;
 *  - insert one or more elements into vector;
 *  - erase, resize, clear and shrink to fit;
 *  - some other stuff.
 */

#include <cmath>
#include <stdexcept>

#include "rao_iterator.hpp"

template<typename T> class Vector
{
    T* _data;
    size_t _size;
    size_t _alloc_size;

    float magnifier = 1.5; // is used when adding elements (insert and etc.)

    void copy_data_to(T* new_data,
                      size_t csize,
                      size_t ref_offset = 0,
                      size_t copy_offset = 0) const // internal function
    {
        for(size_t i = 0; i < csize; ++i) {
            new_data[i + copy_offset] = _data[i + ref_offset];
        }
    }

  public:
    Vector() // defaults
    {
        _data = nullptr;
        _size = 0;
        _alloc_size = 0;
    }

    explicit Vector(const size_t& new_size, float custom_magnifier = 1.5)
    {
        magnifier = custom_magnifier;
        _size = 0;
        _alloc_size = new_size + 1;
        _data = new T[_alloc_size];
    }

    explicit Vector(const Vector& origin_v, float custom_magnifier = 1.5)
    {
        // copy constructor, note the copy is not really equal to the ref.
        magnifier = custom_magnifier;
        _alloc_size = std::round(origin_v.size() * magnifier);
        _data = new T[_alloc_size];
        _size = origin_v.size();
        origin_v.copy_data_to(_data, _size);
    }

    T& at(const size_t& index) // get element by its position
    {
        if(index >= size())
            throw std::out_of_range(
              "Access of non-existent item (index >= size()).");
        // throw an exception
        return _data[index];
    }

    // the same as above, but does no checks
    T& operator[](const size_t& index)
    {
        return _data[index];
    }

    // get the first
    T& front()
    {
        return _data[0];
    }

    // get the last
    T& back()
    {
        return _data[_size - 1];
    }

    // get pointer of the first
    T* data()
    {
        return _data;
    }

    size_t size() const
    {
        return _size;
    }

    // we always have a phantom 'end' element so capacity!=allocated_size
    size_t capacity() const
    {
        return _alloc_size - 1;
    }

    size_t allocated_size() const
    {
        return _alloc_size;
    }

    // iterators for range based for
    RAO_iterator<T> begin()
    {
        return RAO_iterator<T>(&_data[0]);
    }
    RAO_iterator<T> end()
    {
        return RAO_iterator<T>(&_data[_size]);
    }

    // is it empty?
    bool empty()
    {
        return _size == 0;
    }

    // reallocate more space or do nothing
    void reserve(size_t new_size)
    {
        if(new_size > capacity()) {
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

    // append an element
    void push_back(T element)
    {
        if(_alloc_size == 0) {
            // if there are no elements then one does not simply multiply
            _alloc_size = std::round(magnifier);
            _data = new T[_alloc_size];
            _data[0] = element;
            ++_size;
        } else if(_size == capacity()) {
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

    // the function that clears the unused space via reallocation
    void shrink_to_fit()
    {
        if(_size == capacity()) {
            return; // if the vector is maxed out then do nothing
        }
        _alloc_size = _size + 1;
        T* new_data = new T[_alloc_size];
        copy_data_to(new_data, _size);
        delete[] _data;
        _data = new_data;
    }

    // insert one or more elements
    void insert(size_t index, const T& element, size_t el_count = 1)
    {
        // firstly check if the index is in the vector
        if(index < _size) {
            if(_size + el_count - 1 < capacity()) {
                // if the capacity is enough to store the vector+new_elements
                // then just shift all elements after the defined index
                for(size_t i = _size - 1; i >= index; --i) {
                    _data[i + el_count] = _data[i];
                }
            } else {
                // else allocate new memory, then copy the part before index
                // to new_data
                // and then copy the part after index to the new_data array
                // with some offset
                _alloc_size = std::round((_alloc_size + el_count) * magnifier);
                T* new_data = new T[_alloc_size];
                copy_data_to(new_data, index);
                copy_data_to(new_data, _size - index, index, index + el_count);
                delete[] _data;
                _data = new_data;
            }
            for(size_t i = index; i < index + el_count; ++i) {
                _data[i] = element;
            }
            _size += el_count;
        } else {
            // if the defined index is not in the vector then throw an exception
            throw std::out_of_range("Index is out of vector");
        }
    }

    void erase(RAO_iterator<T> iter)
    {
        if(empty()) {
            return;
        }
        size_t copy_offset = distance(begin(), iter);
        size_t ref_offset = copy_offset + 1;
        --_size;
        copy_data_to(_data, _size, ref_offset, copy_offset);
    }

    void erase(RAO_iterator<T> iter_first, RAO_iterator<T> iter_last)
    {
        if(empty()) {
            return;
        }
        size_t esize = distance(iter_first, iter_last);
        size_t csize = distance(iter_last, end());
        size_t begin_pos = distance(begin(), iter_first);
        copy_data_to(_data, csize, begin_pos + esize, begin_pos);
        _size -= esize;
    }

    void pop_back()
    {
        if(!empty()) {
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
        if(new_size == _size)
            return;
        if(new_size > capacity()) {
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

    Vector<T>& operator=(Vector& vec)
    {
        if(_data != nullptr)
            delete[] _data;
        _size = vec._size;
        _alloc_size = _size; // creating a copy only of defined elements
        if(_alloc_size > 0) {
            _data = new T[_alloc_size];
            for(size_t i = 0; i < _size; ++i) {
                _data[i] = vec._data[i];
            }
        } else {
            _data = nullptr;
        }
        return *this;
    }

    template<typename TF> friend void swap(Vector<TF>& v0, Vector<TF>& v1);

    ~Vector()
    {
        delete[] _data;
    }
};

template<typename TF>
void
swap(Vector<TF>& v0,
     Vector<TF>& v1) // swapping contents (magnifiers are not swapped)
{
    TF* tmp = v0._data;
    v0._data = v1._data;
    v1._data = tmp;

    size_t tmp_size = v0._size;
    v0._size = v1._size;
    v1._size = tmp_size;

    tmp_size = v0._alloc_size;
    v0._alloc_size = v1._alloc_size;
    v1._alloc_size = tmp_size;
}

#endif
