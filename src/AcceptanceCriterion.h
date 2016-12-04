//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_ACCEPTANCECRITERION_H
#define HYBRID_ALNS_ACCEPTANCECRITERION_H

#include <random>
#include "Params.h"
#include "Solution.h"

class AcceptanceCriterion {
protected:
    const Params& alns_params;
    mutable std::mt19937* mt;

public:
    AcceptanceCriterion(const Params& alns_params, std::mt19937* mt) : alns_params{alns_params}, mt{mt} {}
    AcceptanceCriterion(const Params& alns_params) : alns_params{alns_params}, mt{nullptr} {}
    void set_mersenne_twister(std::mt19937* mt) { this->mt = mt; }
    virtual bool operator()(const Solution *const incumbent, const Solution *const current, const Solution *const best, uint32_t iteration_number) const = 0;
};

#endif //HYBRID_ALNS_ACCEPTANCECRITERION_H
