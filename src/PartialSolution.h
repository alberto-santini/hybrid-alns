//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_PARTIALSOLUTION_H
#define HYBRID_ALNS_PARTIALSOLUTION_H

#include "Instance.h"

class PartialSolution {
    const Instance const* instance;

public:

    PartialSolution(const Instance const* instance) : instance{instance} {}
};

#endif //HYBRID_ALNS_PARTIALSOLUTION_H
