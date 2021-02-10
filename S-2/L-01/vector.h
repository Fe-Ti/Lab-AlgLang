// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector
#include <ostream>

#ifndef VECTOR
#define VECTOR
template<typename T>
class Vector
{
    T* v_data;       // actual array
    uint64_t v_size; // used by size()

  public:
    Vector();                 // default constructor
    Vector(uint64_t nv_size); // constructor with params

    uint64_t size(); // returns vector size
    T* data();       // access to the raw array

    T& operator[](const uint64_t index);

    void push_back(T node); // todo
    uint64_t find(T node); 
    void replace(T node0, T node1);
    void replace(T node0, T node1, uint64_t count);
    
    ~Vector(); // destructor
};
#endif