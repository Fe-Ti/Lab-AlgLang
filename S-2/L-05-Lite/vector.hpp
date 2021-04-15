// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector

#ifndef VECTOR
#define VECTOR

#include <ostream>

#include <exception>

template<typename T> class Vector
{
    T* v_data;             // actual array
    uint64_t v_size;       // used by size()
    uint64_t v_alloc_size; // allocated memory size (in T-units)

  public:
    Vector() noexcept;                  // default constructor
    Vector(uint64_t nv_size) noexcept;  // constructor with params
    Vector(const Vector& vec) noexcept; // copy constructor

    T* data() noexcept; // access to the raw array
    bool empty() const noexcept;
    uint64_t size() const noexcept;     // returns vector size
    uint64_t capacity() const noexcept; // returns amount of allocated elements

    T& operator[](const uint64_t index);
    T& at(const uint64_t index);

    void push_back(T node);

    Vector<T>& operator=(Vector& vec) noexcept;
    Vector<T>& operator=(Vector<T>&& vec) noexcept;

    ~Vector() noexcept; // destructor
};

#endif