//
// Created by Alberto Santini on 20/11/2016.
//

#include "ALNSSolver.h"

ALNSSolver::ALNSSolver(const Instance const* instance, AcceptanceCriterion const* acceptance, const LocalSearchOperator const* local_search) :
        instance{instance}, acceptance{acceptance}, local_search{local_search}
{
    std::mt19937::result_type random_data[std::mt19937::state_size];
    std::random_device source;
    std::generate(std::begin(random_data), std::end(random_data), std::ref(source));
    std::seed_seq seeds(std::begin(random_data), std::end(random_data));
    mt = std::mt19937(seeds);

    this->acceptance->set_mersenne_twister(&mt);
}
