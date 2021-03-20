// Copyright 2021 Fe-Ti <btm.007@mail.ru>
//
#include <vector>

#include "ParallelCon.hpp"
#include "SequentialCon.hpp"

int
main()
{
    std::vector<ResistorConnection*> vec;
    for(uint64_t i = 0; i < 10; ++i) {
        vec.push_back(new SequentialRCon(i, i * 2));
        vec.push_back(new ParallelRCon(i, i + 2));
    }
    for(auto i : vec) {
        i->print();
        delete i;
        i = nullptr;
    }
    return 0;
}