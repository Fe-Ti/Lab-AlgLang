// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
#include "SequentialCon.hpp"

SequentialRCon::SequentialRCon(float ir1, float ir2)
{
    r1 = ir1;
    r2 = ir2;
}

float
SequentialRCon::calculate_resistance() const
{
    return r1 + r2;
}
void
SequentialRCon::print() const
{
    std::cout << "Sequential connection:" << std::endl;
    std::cout << "    Resistor R1 = " << r1 << " Ohms" << std::endl;
    std::cout << "    Resistor R2 = " << r2 << " Ohms" << std::endl;
    std::cout << "    Overall resistance is " << calculate_resistance();
    std::cout << " Ohms" << std::endl;
}
