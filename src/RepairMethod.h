//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_REPAIRMETHOD_H
#define HYBRID_ALNS_REPAIRMETHOD_H

#include <random>
#include "Params.h"
#include "Instance.h"
#include "TabuMove.h"
#include "Solution.h"
#include "PartialSolution.h"

class RepairMethod {
    const Params& params;
    const Instance const* instance;
    float score;
    const TabuList& tabu_list;
    mutable std::mt19937& mt;

public:

    RepairMethod(const Params& params, const Instance const* instance, const TabuList& tabu_list,  std::mt19937& mt) :
            params{params}, instance{instance}, score{params.initial_repair_score}, tabu_list{tabu_list}, mt{mt} {}

    virtual Solution* operator()(const PartialSolution const* partial_solution, const TabuList& tabu_list) const = 0;
};

#endif //HYBRID_ALNS_REPAIRMETHOD_H
