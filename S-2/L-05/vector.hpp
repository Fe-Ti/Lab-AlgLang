// Copyright 2021 Fe-Ti <btm.007@mail.ru>
#ifndef VECTOR
#define VECTOR

template<typename T>
class Vector
{
    T* _data;
    size_t _size;
    size_t _alloc_size;

    float magnifier = 1.5;

  public:
    Vector()
    {
        _data = nullptr;
        _size = 0;
        _alloc_size = 0;
    }
    Vector(const size_t& size)
    {
        _data = new T[size];
        _alloc_size = size;
    }

    T& at(const size_t& index)
    {
        if(index > size())
            throw std::out_of_range();
        return _data[index];
    }
    operator[](const size_t& index)
    {
        return _data[index];
    }

    T& front()
    {
        return _data[0];
    }

    T& back()
    {
        return _data[_size - 1];
    }

    T* data()
    {
        return _data;
    }

    size_t size() const
    {
        return _size;
    }

    size_t capacity() const
    {
        return _alloc_size - 1;
    }

    size_t allocated_size() const
    {
        return _alloc_size;
    }

    RAO_iterator begin()
    {
        return RAO_iterator(&_data[0]);
    }

    RAO_iterator end()
    {
        return RAO_iterator(&_data[_size]);
    }

    bool empty()
    {
        return _size == 0;
    }
    //////////////////////////////////
    void reserve(size_t new_size)
    {
    }
    //////////////////////////////////
    void insert(size_t index)
    {
    }
    void erase(RAO_iterator iter)
    {
    }
    void erase(RAO_iterator iter_first, RAO_iterator iter_last)
    {
    }

    void push_back(T element)
    {
    }
    void pop_back()
    {
    }

    void resize(size_t new_size)
    {
    }

    friend inline void swap(Vector& v0, Vector& v1);

    void clear()
    {
        delete[] _data;
        _size = 0;
        _alloc_size = 0;
    }

    ~Vector()
    {
        delete[] _data;
    }
};

void
swap(Vector& v0, Vector& v1)
{
}

#endif
