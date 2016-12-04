//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_DESTROYMETHOD_H
#define HYBRID_ALNS_DESTROYMETHOD_H

#include <random>
#include "Params.h"
#include "Solution.h"
#include "PartialSolution.h"
#include "DRMethod.h"

class DestroyMethod : public DRMethod {
public:
    DestroyMethod(const Params& alns_params, std::string name, std::mt19937* mt) : DRMethod{alns_params, name, mt} {}
    DestroyMethod(const Params& alns_params, std::string name) : DRMethod{alns_params, name} {}
    virtual ~DestroyMethod() {}

    virtual PartialSolution* operator()(const Solution *const solution) const = 0;
};

#endif //HYBRID_ALNS_DESTROYMETHOD_H
