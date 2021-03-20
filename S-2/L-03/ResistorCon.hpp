// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
#ifndef RESISTORCON
#define RESISTORCON

#include <iostream>

class ResistorConnection // abstract class
{
  public:
    virtual float calculate_resistance() const = 0;
    virtual void print() const = 0;
    virtual ~ResistorConnection();
};

#endif