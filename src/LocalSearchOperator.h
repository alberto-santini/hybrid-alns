//
// Created by Alberto Santini on 20/11/2016.
//

#ifndef HYBRID_ALNS_LOCALSEARCHOPERATOR_H
#define HYBRID_ALNS_LOCALSEARCHOPERATOR_H

#include "Solution.h"

struct LocalSearchOperator {
    virtual void operator()(Solution *const solution) const = 0;
};

#endif //HYBRID_ALNS_LOCALSEARCHOPERATOR_H
