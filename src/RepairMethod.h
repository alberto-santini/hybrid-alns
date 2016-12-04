//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_REPAIRMETHOD_H
#define HYBRID_ALNS_REPAIRMETHOD_H

#include <random>
#include "Params.h"
#include "TabuMove.h"
#include "Solution.h"
#include "PartialSolution.h"
#include "DRMethod.h"

class RepairMethod : public DRMethod {
protected:
    TabuList* tabu_list;

public:
    RepairMethod(const Params& alns_params, std::string name, std::mt19937* mt) : DRMethod{alns_params, name, mt} {}
    RepairMethod(const Params& alns_params, std::string name) : DRMethod{alns_params, name} {}
    virtual ~RepairMethod() {}

    void set_tabu_list(TabuList* tabu_list) { this->tabu_list = tabu_list; }
    virtual Solution* operator()(const PartialSolution *const partial_solution, uint32_t iter) = 0;
};

#endif //HYBRID_ALNS_REPAIRMETHOD_H
