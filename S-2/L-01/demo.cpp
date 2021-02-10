// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector (Demo)

#include <iostream>

#include "vector.h"

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
    Vector<int> tester0;
    Vector<int> tester1(10);

    tester1[2] = 10;
    std::cout << tester1 << std::endl;
    // std::cout << tester0 << std::endl;
    return 0;
}
