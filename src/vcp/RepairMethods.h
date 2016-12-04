//
// Created by alberto on 24/11/16.
//

#ifndef HYBRID_ALNS_REPAIRMETHODS_H
#define HYBRID_ALNS_REPAIRMETHODS_H

#include "../RepairMethod.h"
#include "VCInstance.h"
#include "Colouring.h"

class GreedyRecolourDegreeAsc : public RepairMethod {
    const VCInstance& instance;

public:
    GreedyRecolourDegreeAsc(const Params& params, const VCInstance& instance) : RepairMethod{params, "greedy recolour degree asc"}, instance{instance} {}
    ~GreedyRecolourDegreeAsc() {}

    Colouring* operator()(const PartialSolution *const partial_solution, uint32_t iter);
};

class GreedyRecolourDegreeDesc : public RepairMethod {
    const VCInstance& instance;

public:
    GreedyRecolourDegreeDesc(const Params& params, const VCInstance& instance) : RepairMethod{params, "greedy recolour degree desc"}, instance{instance} {}
    ~GreedyRecolourDegreeDesc() {}

    Colouring* operator()(const PartialSolution *const partial_solution, uint32_t iter);
};

class GreedyRecolourColourDegreeAsc : public RepairMethod {
    const VCInstance& instance;

public:
    GreedyRecolourColourDegreeAsc(const Params& params, const VCInstance& instance) : RepairMethod{params, "greedy recolour colour degree asc"}, instance{instance} {}
    ~GreedyRecolourColourDegreeAsc() {}

    Colouring* operator()(const PartialSolution *const partial_solution, uint32_t iter);
};

class GreedyRecolourColourDegreeDesc : public RepairMethod {
    const VCInstance& instance;

public:
    GreedyRecolourColourDegreeDesc(const Params& params, const VCInstance& instance) : RepairMethod{params, "greedy recolour colour degree desc"}, instance{instance} {}
    ~GreedyRecolourColourDegreeDesc() {}

    Colouring* operator()(const PartialSolution *const partial_solution, uint32_t iter);
};

class MWSSRecolour : public RepairMethod {
    const VCInstance& instance;

public:
    MWSSRecolour(const Params& params, const VCInstance& instance) : RepairMethod{params, "mwss recolour"}, instance{instance} {}
    ~MWSSRecolour() {}

    Colouring* operator()(const PartialSolution *const partial_solution, uint32_t iter);
};

class GreedyAndMWSSRecolour : public RepairMethod {
    const VCInstance& instance;

public:
    GreedyAndMWSSRecolour(const Params& params, const VCInstance& instance) : RepairMethod{params, "greedy + mwss recolour"}, instance{instance} {}
    ~GreedyAndMWSSRecolour() {}

    Colouring* operator()(const PartialSolution *const partial_solution, uint32_t iter);
};

#endif //HYBRID_ALNS_REPAIRMETHODS_H
