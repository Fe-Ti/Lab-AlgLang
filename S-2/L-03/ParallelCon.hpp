// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
#ifndef PARALLELCON
#define PARALLELCON

#include "ResistorCon.hpp"

class ParallelRCon : public ResistorConnection
{
  protected:
    float r1;
    float r2;

  public:
    ParallelRCon(float ir1, float ir2);
    float calculate_resistance() const override;
    void print() const override;
};

#endif