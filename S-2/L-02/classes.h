// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
// Region+Family

#ifndef RFAMILY
#define RFAMILY

#include <iostream>
#include <string>

class Family
{
  protected:
    std::string surname;
    uint16_t member_count;
    uint64_t total_income;

  public:
    Family(std::string s_name, uint16_t m_count, uint64_t t_income);
    long double average_income() const;
    void print_status() const;
    ~Family();
};

class Region
{
  protected:
    std::string r_name;
    uint64_t payoff_size;
    uint64_t aver_income_threshold;

  public:
    Region(std::string name, uint64_t p_size, uint64_t ai_threshold);
    void print_status() const;
    ~Region();
};

class RegionFamily
  : public Family
  , public Region
{
  public:
    RegionFamily(std::string s_name,
                 uint16_t m_count,
                 uint64_t t_income,
                 std::string name,
                 uint64_t p_size,
                 uint64_t ai_threshold);
    long double average_income() const;
    void print_status() const;
    ~RegionFamily();
};

#endif