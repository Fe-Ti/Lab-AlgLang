// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector

#include "vector.h"

Vector::Vector()
{
    size = 0;
}

Vector::Vector(uint64_t& v_size)
{
    size = v_size;
    if(v_size > 0)
        data = new T[v_size];
}

std::ostream&
Vector::operator<<(std::ostream& t_out)
{
    for(uint64_t i = 0; i < size; ++i) {
        t_out << data[i] << " ";
    }
}

T&
Vector::operator[](uint64_t& index)
{
    return data[index];
}

Vector::~Vector()
{
    delete[] data;
}