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
    int a;
    std::cout << "Enter the number of elements:" << std::endl;
    std::cin >> a;
    Vector<int> tester1(10);

    tester1[2] = 10;
    std::cout << "Changed the 3d element, other are undefined:" << std::endl;
    std::cout << tester1 << std::endl;

    for(int i = 0; i < a; ++i) {
        tester1[i] = i;
    }
    std::cout << "Here is your vector filled with numbers:" << std::endl;
    std::cout << tester1 << std::endl;

    std::cout << "Searching for " << a - 6 << std::endl;
    std::cout << a - 6 << " is on " << tester1.find(a - 6) << " position"
              << std::endl;

    tester1.replace(0, 6);
    std::cout << "Replaced one 0 with 6" << std::endl;
    std::cout << tester1 << std::endl;

    tester1.replace(6, 1, 100);
    std::cout
      << "Replaced 100 numbers 6 with 1 (actually there were only two of them)"
      << std::endl;
    std::cout << tester1 << std::endl;

    tester1.replace(1, 10);
    std::cout << "Replaced one 1 with 10" << std::endl;
    std::cout << tester1 << std::endl;

    std::cout << "Searched for 6, but failed" << std::endl;
    std::cout << tester1.find(6) << std::endl;

    std::cout << "Moving forward..." << std::endl;
    std::cout << "Now the vector size is ";
    std::cout << tester1.size() << std::endl;

    std::cout << "Here is the subject of our experiment" << std::endl;
    std::cout << tester1 << std::endl;
    std::cout << "Its allocated size is " << tester1.allocated_size();
    std::cout << " elements." << std::endl;

    std::cout << "Pushing back 12345" << std::endl;
    tester1.push_back(12345);
    std::cout << "Here is the subject of our experiment again" << std::endl;
    std::cout << tester1 << std::endl;
    std::cout << "its size is " << tester1.size() << std::endl;
    std::cout << "and its allocated size is " << tester1.allocated_size();
    std::cout << " elements." << std::endl;

    Vector<int> tester0(tester1);
    std::cout << "Here is the copy of your vector:" << std::endl;
    std::cout << tester0 << std::endl;
    std::cout << "Its allocated size is " << tester0.allocated_size();
    std::cout << " elements." << std::endl;
    std::cout << "Pushing back 77" << std::endl;
    tester0.push_back(77);
    std::cout << "Here is this vector:" << std::endl;
    std::cout << tester0 << std::endl;
    std::cout << "Its allocated size is " << tester0.allocated_size();
    std::cout << " elements." << std::endl;
    return 0;
}
