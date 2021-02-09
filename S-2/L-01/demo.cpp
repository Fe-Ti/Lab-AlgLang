// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Yet Another Vector (Demo)

#include <iostream>

#include "vector.h"

int
main()
{
    Vector tester0<int>;
    Vector tester1<uint64_t>(10);
    
    tester1[2] = 10;
    std::cout << tester1 << std::endl;
    std::cout << tester0 << std::endl;
    return 0;
}
