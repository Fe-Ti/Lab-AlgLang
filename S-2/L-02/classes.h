// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
// Region+Family

#ifndef RFAMILY
#define RFAMILY

#include <iostream>
#include <string>

class Family
{
    std::string surname;
    uint16_t member_count;
    uint64_t total_income;

  public:
    Family(std::string s_name, uint16_t m_count, uint64_t t_income);
    uint64_t average_income() const;
    void print_status() const;
    ~Family();
}

class Region
{
    std::string r_name;
    uint64_t payoff_size;
    uint64_t aver_income_threshold;

  public:
    Region(std::string name, uint64_t p_size, uint64_t ai_threshold);
    void print_status() const;
    ~Region();
}

class RegionFamily
  : public Family
  , public Region
{
  public:
    RegionFamily(Family f, Region r);
    RegionFamily(std::string s_name,
                 uint16_t m_count,
                 uint64_t t_income,
                 std::string name,
                 uint64_t p_size,
                 uint64_t ai_threshold);
    uint64_t average_income();
    void print_status() const;
    ~RegionFamily();
}

#endif