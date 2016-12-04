//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_PARAMS_H
#define HYBRID_ALNS_PARAMS_H

#include <cstdint>
#include <string>

struct Params {
    float initial_destroy_score;
    float initial_repair_score;
    float new_best_score_update;
    float improves_current_score_update;
    float accepted_score_update;
    float rejected_score_update;
    float history_weight_in_score_update;
    uint32_t tabu_tenure;
    uint32_t alns_iterations;
    uint32_t column_optimisation_frequency;
    uint32_t column_optimisation_timeout;

    Params(std::string filename);
};

#endif //HYBRID_ALNS_PARAMS_H
