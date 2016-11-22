//
// Created by Alberto Santini on 20/11/2016.
//

#ifndef HYBRID_ALNS_LOCALSEARCHOPERATOR_H
#define HYBRID_ALNS_LOCALSEARCHOPERATOR_H

#include "Instance.h"
#include "Solution.h"

class LocalSearchOperator {
    const Instance const* instance;

public:
    LocalSearchOperator(const Instance const* instance) : instance{instance} {}
    virtual Solution* operator()(const Solution const* solution) const = 0;
};

#endif //HYBRID_ALNS_LOCALSEARCHOPERATOR_H
