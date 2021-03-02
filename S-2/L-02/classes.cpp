// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
// Region+Family
#include "classes.h"

Family::Family(std::string s_name, uint16_t m_count, uint64_t t_income)
{
    surname = s_name;
    member_count = m_count;
    total_income = t_income;
}
uint64_t
Family::average_income() const
{
    return total_income / std::static_cast<float>(member_count);
}

void
Family::print_status() const
{
    std::cout << "Family surname " << surname << std::endl;
    std::cout << "Family member count " << member_count << std::endl;
    std::cout << "Family total income " << total_income << std::endl;
}

Family::~Family()
{
    std::cout << "Destroyed an object of the class Family" << std::endl;
}

Region::Region(std::string name, uint64_t p_size, uint64_t ai_threshold)
{
    r_name = name;
    payoff_size = p_size;
    aver_income_threshold = ai_threshold;
}

void
Region::print_status() const
{
    std::cout << "Region name" << r_name << std::endl;
    std::cout << "Region payoff size" << payoff_size << std::endl;
    std::cout << "Region average income threshold" << aver_income_threshold
              << std::endl;
}

Region::~Region()
{
    std::cout << "Destructing object of the class Region" << std::endl;
}

RegionFamily(Family f, Region r)
{
}
RegionFamily(std::string s_name,
             uint16_t m_count,
             uint64_t t_income,
             std::string name,
             uint64_t p_size,
             uint64_t ai_threshold)
{
}

uint64_t
RegionFamily::average_income() const
{
    return (total_income + payoff_size) / static_cast<float>(member_count);
}

void
RegionFamily::print_status() const
{
    std::cout << "Destructing a RegionFamily object" << std::endl;
}
