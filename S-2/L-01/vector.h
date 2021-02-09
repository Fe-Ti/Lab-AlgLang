// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector
#include <ostream>

template<typename T> class Vector
{
    T* data;
    uint64_t size;

  public:
    Vector();
    Vector(uint64_t& v_size);
    std::ostream& operator<<(std::ostream& t_out);
    T& operator[](uint64_t& index);
    ~Vector();
};
