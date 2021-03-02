// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
// Region+Family
#include "classes.h"

Family::Family(std::string s_name, uint16_t m_count, uint64_t t_income)
{
    surname;
}
uint64_t
Family::average_income() const
{
}

void
Family::print_status() const
{
    std::cout << "Region name" << std::endl;
}

Family::~Family()
{
    std::cout << "Destroyed an object of Family type" << std::endl;
}

Region::Region(std::string name, uint64_t p_size, uint64_t ai_threshold)
{
}

void
Region::print_status() const
{
    std::cout << "Region name" << std::endl;
    std::cout << "Region payoff size" << std::endl;
    std::cout << "Region average income threshold" << std::endl;
}

Region::~Region()
{
}

uint64_t
RegionFamily::average_income()
{
}

void
RegionFamily::print_status() const
{
}
