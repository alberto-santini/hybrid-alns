//
// Created by alberto on 01/12/16.
//

#ifndef HYBRID_ALNS_MWSS_H
#define HYBRID_ALNS_MWSS_H

#include "VCInstance.h"
#include "Colouring.h"

extern "C" {
    #include <exactcolors/mwis_sewell/mwss.h>
    #include <exactcolors/mwis_sewell/mwss_ext.h>
}

class MWSS {
    using Vertex = Colouring::Vertex;
    using Colour = Colouring::Colour;

    const VCInstance& instance;

public:
    MWSS(const VCInstance& instance) : instance{instance} {}
    Colour largest_stable_set_for(const std::vector<Vertex>& vertices) const;
    std::vector<Colour> all_stable_sets_for(const std::vector<Vertex>& vertices) const;
};

#endif //HYBRID_ALNS_MWSS_H
