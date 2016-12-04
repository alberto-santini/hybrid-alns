//
// Created by alberto on 24/11/16.
//

#ifndef HYBRID_ALNS_VCTABUMOVE_H
#define HYBRID_ALNS_VCTABUMOVE_H

#include "../TabuMove.h"
#include "VCInstance.h"

struct VCTabuMove : public TabuMove {
    using Vertex = VCInstance::Vertex;

    Vertex vertex;
    uint32_t colour;

    VCTabuMove(Vertex vertex, uint32_t colour, uint32_t valid_until) : TabuMove{valid_until}, vertex{vertex}, colour{colour} {}
    ~VCTabuMove() {}
    std::ostream& format(std::ostream& out) const;
};

#endif //HYBRID_ALNS_VCTABUMOVE_H
