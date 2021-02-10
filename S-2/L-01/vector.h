// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector
#include <ostream>

#ifndef VECTOR
#define VECTOR
template<typename T>
class Vector
{
    T* v_data;
    uint64_t v_size;

  public:
    Vector();
    Vector(uint64_t nv_size);

    uint64_t size();
    T* data();

    T& operator[](const uint64_t index);

    ~Vector();
};
#endif