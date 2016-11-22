//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_ACCEPTANCECRITERION_H
#define HYBRID_ALNS_ACCEPTANCECRITERION_H

#include <random>
#include "Params.h"
#include "Instance.h"
#include "Solution.h"

class AcceptanceCriterion {
    const Params& params;
    const Instance const* instance;
    mutable std::mt19937* mt;

public:
    AcceptanceCriterion(const Params& params, const Instance const* instance, std::mt19937* mt) : params{params}, instance{instance}, mt{mt} {}
    AcceptanceCriterion(const Params& params, const Instance const* instance) : params{params}, instance{instance} {}
    void set_mersenne_twister(std::mt19937* mt) { this->mt = mt; }
    virtual bool operator()(const Solution* incumbent, const Solution* current, const Solution* best, uint32_t iteration_number) const = 0;
};

#endif //HYBRID_ALNS_ACCEPTANCECRITERION_H
