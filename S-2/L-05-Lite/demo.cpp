// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector (Demo)

#include <iostream>

#include "vector.hpp"

template<typename T>
std::ostream&
operator<<(std::ostream& t_out, Vector<T>& vec)
{
    for(uint64_t i = 0; i < vec.size(); ++i) {
        t_out << vec[i] << " ";
    }
    return t_out;
}

int
main()
{
    return 0;
}
