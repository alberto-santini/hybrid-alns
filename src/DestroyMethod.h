//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_DESTROYMETHOD_H
#define HYBRID_ALNS_DESTROYMETHOD_H

#include <random>
#include "Instance.h"
#include "Params.h"
#include "Solution.h"
#include "PartialSolution.h"

class DestroyMethod {
    const Params& params;
    const Instance const* instance;
    float score;
    mutable std::mt19937* mt;

public:
    DestroyMethod(const Params& params, const Instance const* instance, std::mt19937* mt) : params{params}, instance{instance}, score{params.initial_destroy_score}, mt{mt} {}
    DestroyMethod(const Params& params, const Instance const* instance) : params{params}, instance{instance}, score{params.initial_repair_score} {}
    void set_mersenne_twister(std::mt19937* mt) { this->mt = mt; }
    virtual PartialSolution* operator()(const Solution const* solution) const = 0;
};

#endif //HYBRID_ALNS_DESTROYMETHOD_H
