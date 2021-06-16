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

template<typename T>
void
print_info(Vector<T>& v)
{
    std::cout << '|' << v << '|' << std::endl
              << " _alloc_size = " << v.allocated_size() << std::endl
              << " _size = " << v.size() << std::endl
              << " capacity() = " << v.capacity() << std::endl;
}

int
main()
{
    Vector<int> v0;
	print_info(v0);
    v0.push_back(34978);
	print_info(v0);
    v0.push_back(53687);
	print_info(v0);
    v0.push_back(25390);
	print_info(v0);
    v0.push_back(8);
	print_info(v0);
    v0.push_back(311);
	print_info(v0);
    v0.insert(3, 69);
	print_info(v0);
    v0.insert(2, 69, 4);
	print_info(v0);
    return 0;
}