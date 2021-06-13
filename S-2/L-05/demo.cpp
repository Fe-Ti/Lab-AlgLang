// Copyright 2021 Fe-Ti <btm.007@mail.ru>
#include "vector.hpp"
#include <iostream>

template<typename T>
std::ostream&
operator<<(std::ostream& out, Vector<T>& v)
{
    for (T& i : v) {
        std::cout << i << " ";
    }
//    std::cout << std::endl;
	return out;
}

int
main()
{
    Vector<int> v0;
    v0.push_back(34978);
    v0.push_back(53687);
    v0.push_back(25390);
    v0.push_back(8);
    v0.push_back(311);
    std::cout << v0 << std::endl;
    return 0;
}