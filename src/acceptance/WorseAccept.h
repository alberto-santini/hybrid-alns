//
// Created by alberto on 24/11/16.
//

#ifndef HYBRID_ALNS_WORSEACCEPT_H
#define HYBRID_ALNS_WORSEACCEPT_H

#include "../AcceptanceCriterion.h"
#include <string>

class WorseAccept : public AcceptanceCriterion {
    float start_probability;
    mutable std::uniform_real_distribution<float> dis;

public:
    WorseAccept(std::string acceptance_params_filename, const Params& alns_params);
    bool operator()(const Solution *const incumbent, const Solution *const current, const Solution *const best, uint32_t iteration_number) const;
};

#endif //HYBRID_ALNS_WORSEACCEPT_H