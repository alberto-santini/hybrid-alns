//
// Created by alberto on 22/11/16.
//

#ifndef HYBRID_ALNS_DRMETHOD_H
#define HYBRID_ALNS_DRMETHOD_H

#include <random>
#include <string>
#include "Params.h"
#include "PartialSolution.h"
#include "Solution.h"

class DRMethod {
protected:
    const Params& alns_params;
    float score;
    std::string name;
    mutable std::mt19937* mt;

public:
    DRMethod(const Params& alns_params, std::string name, std::mt19937* mt) : alns_params{alns_params}, name{name}, mt{mt} {}
    DRMethod(const Params& alns_params, std::string name) : alns_params{alns_params}, name{name}, mt{nullptr} {}
    void set_mersenne_twister(std::mt19937* mt) { this->mt = mt; }
    void set_score(float score) { this->score = score; }
    float get_score() const { return score; }
    std::string get_name() const { return name; }
};

#endif //HYBRID_ALNS_DRMETHOD_H
