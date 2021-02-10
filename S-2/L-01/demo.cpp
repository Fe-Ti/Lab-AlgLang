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
    int a = 10;
    //    Vector<int> tester0;
    Vector<int> tester1(10);

    tester1[2] = 10;
    std::cout << tester1 << std::endl;

    for(int i = 0; i < a; ++i) {
        tester1[i] = i;
    }
    std::cout << tester1 << std::endl;
    std::cout << tester1.find(a - 6) << std::endl;
    tester1.replace(10, 6);
    std::cout << tester1 << std::endl;
    tester1.replace(6, 1, 100);
    std::cout << tester1 << std::endl;
    tester1.replace(1, 10);
    std::cout << tester1 << std::endl;
    std::cout << tester1.find(6) << std::endl;
    std::cout << tester1.size() << std::endl;
    // std::cout << tester1 << std::endl;
    //   std::cout << tester1 << std::endl;
    // std::cout << tester0 << std::endl;
    return 0;
}
