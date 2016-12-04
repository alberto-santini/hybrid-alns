//
// Created by Alberto Santini on 20/11/2016.
//

#include <memory>
#include <algorithm>
#include <functional>
#include <assert.h>
#include <iostream>
#include "ALNSSolver.h"

ALNSSolver::ALNSSolver(const Params& params, AcceptanceCriterion *const acceptance, ColumnOptimiser *const copt, const LocalSearchOperator *const local_search) :
        alns_params{params}, acceptance{acceptance}, copt{copt}, local_search{local_search}
{
    std::mt19937::result_type random_data[std::mt19937::state_size];
    std::random_device source;
    std::generate(std::begin(random_data), std::end(random_data), std::ref(source));
    std::seed_seq seeds(std::begin(random_data), std::end(random_data));
    mt = std::mt19937(seeds);

    this->acceptance->set_mersenne_twister(&mt);
    if(this->copt) { this->copt->set_timeout(params.column_optimisation_timeout); }
}

Solution* ALNSSolver::solve(const Solution *const initial_solution) {
    init_destroy_methods();
    init_repair_methods();

    uint32_t current_iteration = 0u;

    Solution* current = initial_solution->clone();
    if(local_search) { (*local_search)(current); }

    Solution* best = current->clone();

    while(++current_iteration <= alns_params.alns_iterations) {
        if(current_iteration % 500 == 0) {
            std::cout << "Iteration: " << current_iteration << std::endl;
        }

        DestroyMethod* destroy_m = roulette_wheel(destroy);
        RepairMethod* repair_m = roulette_wheel(repair);
        std::unique_ptr<PartialSolution> partial = nullptr;
        std::unique_ptr<Solution> incumbent = nullptr;

        if( copt != nullptr &&
            current_iteration > 0u &&
            current_iteration % alns_params.column_optimisation_frequency == 0)
        {
            std::cout << "Column optimisation (" << column_pool.size() << " columns)..." << std::endl;
            auto optimised_solution = copt->optimise(column_pool);
            if(optimised_solution != nullptr) {
                incumbent = std::unique_ptr<Solution>(optimised_solution);

                std::cout << "Column optimisation solution: ";
                optimised_solution->print_summary();
            } else {
                std::cerr << "The column optimiser encountered an error!" << std::endl;
            }
        }

        if(!incumbent){
            destroy_m = roulette_wheel(destroy);
            repair_m = roulette_wheel(repair);
            partial = std::unique_ptr<PartialSolution>((*destroy_m)(current));
            incumbent = std::unique_ptr<Solution>((*repair_m)(partial.get(), current_iteration));
        }

        if(local_search) { (*local_search)(incumbent.get()); }
        update_pool(incumbent.get());

        if((*acceptance)(incumbent.get(), current, best, current_iteration)) {
            if(incumbent->obj_value() < best->obj_value()) {
                update_score(destroy_m, alns_params.new_best_score_update);
                update_score(repair_m, alns_params.new_best_score_update);

                delete best;
                best = incumbent->clone();

                std::cout << "New best at iter " << current_iteration << "! ";
                best->print_summary();
            } else if(incumbent->obj_value() < current->obj_value()) {
                update_score(destroy_m, alns_params.improves_current_score_update);
                update_score(repair_m, alns_params.improves_current_score_update);
            } else {
                update_score(destroy_m, alns_params.accepted_score_update);
                update_score(repair_m, alns_params.accepted_score_update);
            }

            delete current;
            current = incumbent->clone();
        } else {
            update_score(destroy_m, alns_params.rejected_score_update);
            update_score(repair_m, alns_params.rejected_score_update);
        }

        clean_up_tabu_list(current_iteration);
    }

    print_methods_scores();

    delete current;
    return best;
}

void ALNSSolver::clean_up_tabu_list(uint32_t current_iteration) {
    for(auto it = tabu_list.begin(); it != tabu_list.end();) {
        if((*it)->valid_until <= current_iteration) {
            assert((*it)->valid_until == current_iteration);
            delete (*it);
            it = tabu_list.erase(it);
        } else {
            ++it;
        }
    }
}

void ALNSSolver::init_repair_methods() {
    for(auto rm_ptr : repair) {
        rm_ptr->set_mersenne_twister(&mt);
        rm_ptr->set_score(alns_params.initial_repair_score);
        rm_ptr->set_tabu_list(&tabu_list);
    }
}

void ALNSSolver::init_destroy_methods() {
    for(auto dm_ptr : destroy) {
        dm_ptr->set_mersenne_twister(&mt);
        dm_ptr->set_score(alns_params.initial_destroy_score);
    }
}

ALNSSolver::~ALNSSolver() {
    for(auto dm_ptr : destroy) { delete dm_ptr; }
    destroy.clear();
    for(auto rm_ptr : repair) { delete rm_ptr; }
    repair.clear();
    for(auto tm_ptr : tabu_list) { delete tm_ptr; }
    tabu_list.clear();
}

void ALNSSolver::print_methods_scores() const {
    std::cout << "Destroy methods:" << std::endl;
    for(auto method : destroy) {
        std::cout << "\t" << method->get_name() << ": " << method->get_score() << std::endl;
    }
    std::cout << "Repair methods:" << std::endl;
    for(auto method: repair) {
        std::cout << "\t" << method->get_name() << ": " << method->get_score() << std::endl;
    }
}

void ALNSSolver::print_tabu_list() const {
    std::cout << "Tabu list (size = " << tabu_list.size() << "):" << std::endl;
    for(auto move : tabu_list) {
        std::cout << *move << std::endl;
    }
}

void ALNSSolver::update_pool(const Solution* const incumbent) {
    for(const auto& column : incumbent->to_columns()) { column_pool.insert(column); }
}
