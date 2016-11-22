//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_PARAMS_H
#define HYBRID_ALNS_PARAMS_H

#include <cstdint>

struct Params {
    float initial_destroy_score;
    float initial_repair_score;
    float new_best_score_update;
    float improves_current_score_update;
    float accepted_score_update;
    float rejected_score_update;
    float history_weight_in_score_update;
    uint32_t tabu_tenure;
};

#endif //HYBRID_ALNS_PARAMS_H
