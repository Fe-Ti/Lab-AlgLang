// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
#ifndef SEQUENTIALCON
#define SEQUENTIALCON

#include "ResistorCon.hpp"

class SequentialRCon : public ResistorConnection
{
  protected:
    float r1;
    float r2;

  public:
    SequentialRCon(float ir1, float ir2);
    float calculate_resistance() const override;
    void print() const override;
};

#endif