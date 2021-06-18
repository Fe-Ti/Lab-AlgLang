// Copyright 2021 Fe-Ti <btm.007@mail.ru>

#ifndef VECTOR
#define VECTOR

/*
 * Stripped down version of vector from L-05
 */

template<typename T> class Vector
{
    T* _data;
    size_t _size;
    size_t _alloc_size;

    float magnifier = 1.5; // is used when adding elements (insert and etc.)

  public:
    Vector() // defaults
    {
        _data = nullptr;
        _size = 0;
        _alloc_size = 0;
    }

    explicit Vector(const size_t& size, float custom_magnifier = 1.5)
    {
        magnifier = custom_magnifier;
        _alloc_size = size;
        _data = new T[size];
    }

    ~Vector()
    {
        delete[] _data;
    }
};

#endif
