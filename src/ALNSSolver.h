//
// Created by Alberto Santini on 20/11/2016.
//

#ifndef HYBRID_ALNS_ALNSSOLVER_H
#define HYBRID_ALNS_ALNSSOLVER_H

#include <random>
#include "Instance.h"
#include "AcceptanceCriterion.h"
#include "LocalSearchOperator.h"
#include "DestroyMethod.h"
#include "RepairMethod.h"

class ALNSSolver {
    const Instance const* instance;
    AcceptanceCriterion const* acceptance;
    const LocalSearchOperator const* local_search;
    std::vector<const DestroyMethod const*> destroy;
    std::vector<const RepairMethod const*> repair;
    TabuList tabu_list;
    mutable std::mt19937 mt;

public:
    ALNSSolver(const Instance const* instance, AcceptanceCriterion const* acceptance, const LocalSearchOperator const* local_search = nullptr);
};

#endif //HYBRID_ALNS_ALNSSOLVER_H
