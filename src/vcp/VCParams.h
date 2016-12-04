//
// Created by alberto on 01/12/16.
//

#ifndef HYBRID_ALNS_VCPARAMS_H
#define HYBRID_ALNS_VCPARAMS_H

#include <string>

struct VCParams {
    float max_fraction_of_colours_to_empty_at_once;

    VCParams(std::string filename);
};

#endif //HYBRID_ALNS_VCPARAMS_H
