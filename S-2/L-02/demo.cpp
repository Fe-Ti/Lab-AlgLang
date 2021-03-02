// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
// Region+Family
#include "classes.h"

int
main()
{

    uint16_t member_count = 10;
    uint64_t total_income0 = 12345;
    uint64_t total_income1 = 123;
    std::string surname0 = "TEST SN0";
    std::string surname1 = "TEST SN1";

    uint64_t payoff_size = 103;
    uint64_t aver_income_threshold = 100;
    std::string r_name = "TEST RN";

    Family f(surname0, member_count, total_income0);
    std::cout << "Family sample object" << std::endl;
    f.print_status();
    std::cout << "Aver. income: " << f.average_income() << std::endl;

    Region r(r_name, payoff_size, aver_income_threshold);
    std::cout << "Region sample object" << std::endl;
    r.print_status();

    RegionFamily rf0(surname0,      // these objects can be initialized
                     member_count,  // via passing a region and family
                     total_income0, // to the constructor
                     r_name,        // but I did not implement such a function
                     payoff_size,   // so I use a simpler variant
                     aver_income_threshold);
    RegionFamily rf1(surname1,
                     member_count,
                     total_income1,
                     r_name,
                     payoff_size,
                     aver_income_threshold);

    std::cout << "RegionFamily sample object #0" << std::endl;
    rf0.print_status();
    std::cout << "Aver. income: " << rf0.average_income() << std::endl;

    std::cout << "RegionFamily sample object #1" << std::endl;
    rf1.print_status();
    std::cout << "Aver. income: " << rf1.average_income() << std::endl;
}
