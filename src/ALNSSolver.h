//
// Created by Alberto Santini on 20/11/2016.
//

#ifndef HYBRID_ALNS_ALNSSOLVER_H
#define HYBRID_ALNS_ALNSSOLVER_H

#include <random>
#include <unordered_set>
#include "AcceptanceCriterion.h"
#include "LocalSearchOperator.h"
#include "DestroyMethod.h"
#include "RepairMethod.h"
#include "Column.h"
#include "ColumnOptimiser.h"

class ALNSSolver {
    const Params& alns_params;

    AcceptanceCriterion *const acceptance;

    ColumnPool column_pool;
    ColumnOptimiser *const copt;

    const LocalSearchOperator *const local_search;

    std::vector<DestroyMethod*> destroy;
    std::vector<RepairMethod*> repair;

    TabuList tabu_list;

    mutable std::mt19937 mt;

public:
    ALNSSolver(const Params& params, AcceptanceCriterion *const acceptance, ColumnOptimiser *const copt = nullptr, const LocalSearchOperator *const local_search = nullptr);
    ~ALNSSolver();

    Solution* solve(const Solution *const initial_solution);
    void add_destroy_method(DestroyMethod* dm) { destroy.push_back(dm); }
    void add_repair_method(RepairMethod* rm) { repair.push_back(rm); }

private:
    void init_destroy_methods();
    void init_repair_methods();
    template<class R> R roulette_wheel(std::vector<R> vec) const;
    template<class R> void update_score(R method, float amount);
    void clean_up_tabu_list(uint32_t current_iteration);
    void print_methods_scores() const;
    void print_tabu_list() const;
    void update_pool(const Solution *const incumbent);
};

#include "ALNSSolver.tpp"

#endif //HYBRID_ALNS_ALNSSOLVER_H
