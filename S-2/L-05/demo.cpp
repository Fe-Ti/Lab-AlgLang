// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
#include "vector.hpp"
#include <iostream>

struct CustomType { // some custom type for testing
    uint64_t smthu6[10];
    double smthd[10];
};

std::ostream&
operator<<(std::ostream& out, CustomType i) // never mind
{
    std::cout << i.smthd[1] << "," << i.smthu6[1];
    return out;
}

template<typename T>
std::ostream&
operator<<(std::ostream& out, Vector<T>& v)
{
    for(T& i : v) {
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
    std::cout << "---- Initializing empty vector ----" << std::endl;
    Vector<int> v0;
    print_info(v0);
    std::cout << "---- Pushing back elements ----" << std::endl;
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
    std::cout << "---- Inserting 1 element 69 ----" << std::endl;
    v0.insert(3, 69);
    print_info(v0);
    std::cout << "---- Inserting 4 elements 69 ----" << std::endl;
    v0.insert(2, 69, 4);
    print_info(v0);
    std::cout << "---- Erasing 1 item from begin ----" << std::endl;
    v0.erase(v0.begin());
    print_info(v0);
    std::cout << "---- Erasing the range from begin()+2 to end()-2 ----"
              << std::endl;
    v0.erase(v0.begin() + 2, v0.end() - 2);
    print_info(v0);
    std::cout << "---- Using copy constructor ----" << std::endl;
    Vector<int> v1(v0);
    print_info(v1);
    std::cout << "---- Using constructor 'vector(v_size)' ----" << std::endl;
    Vector<int> v2(10);
    print_info(v2);
    std::cout << "---- Using custom type ----" << std::endl;
    Vector<CustomType> vcu(3);
    print_info(vcu);
    std::cout << "---- Accessing something via [] in custom type vector ----"
              << std::endl;
    std::cout << "before:" << std::endl;
    std::cout << vcu[1] << std::endl; // The value isn't initialized but...
    vcu[1].smthd[1] = 5;              // Never mind
    std::cout << "after:" << std::endl;
    std::cout << vcu[1] << std::endl;
    std::cout << "---- Accessing an element which does not exist ----"
              << std::endl;
    try {
        v1.at(v1.size());
    } catch(const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---- Popping back ----" << std::endl;
    print_info(v1);
    v1.pop_back();
    print_info(v1);
    std::cout << "---- Using operator= ----" << std::endl;
    print_info(v2);
    v2 = v0;
    print_info(v2);
    std::cout << "---- Swapping vectors ----" << std::endl;
    v0.shrink_to_fit();
    v1.shrink_to_fit();
    std::cout << "before:" << std::endl;
    std::cout << "v0 = " << v0 << std::endl;
    std::cout << "v1 = " << v1 << std::endl;
    swap(v0, v1);
    std::cout << "after:" << std::endl;
    std::cout << "v0 = " << v0 << std::endl;
    std::cout << "v1 = " << v1 << std::endl;
    // std::cout << "----  ----" << std::endl;
    return 0;
}