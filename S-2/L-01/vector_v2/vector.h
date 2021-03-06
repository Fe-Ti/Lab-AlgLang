// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector (size via ptr tp the last)
#include <ostream>

#ifndef VECTOR
#define VECTOR

template<typename T>
class Vector
{
    T* v_data;             // actual array
    T* v_back;              // used by size()
    uint64_t v_alloc_size; // allocated memory size (in T-units)

  public:
    Vector();                 // default constructor
    Vector(uint64_t nv_size); // constructor with params
    Vector(Vector& vec);      // copy constructor

    uint64_t size() const;           // returns vector size
    uint64_t allocated_size() const; // returns amount of allocated elements
    T* data() const;                 // access to the raw array
    T* back() const;
    T& operator[](const uint64_t index);

    void push_back(T node);

    uint64_t find(T node) const;
    void replace(T node0, T node1);
    void replace(T node0, T node1, uint64_t count);

    ~Vector(); // destructor
};

#endif