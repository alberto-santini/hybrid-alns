//
// Created by alberto on 24/11/16.
//

#ifndef HYBRID_ALNS_GREEDYCOLOUR_H
#define HYBRID_ALNS_GREEDYCOLOUR_H

#include "VCInstance.h"
#include "Colouring.h"
#include "VCTabuMove.h"

class GreedyColour {
    const VCInstance& instance;

public:
    using Vertex = VCInstance::Vertex;
    using NewColourAssignments = std::map<Vertex, uint32_t>;

    enum class VertexSortingCriterion {
        DEGREE_ASC, DEGREE_DESC,
        COLOUR_DEGREE_ASC, COLOUR_DEGREE_DESC
    };

    GreedyColour(const VCInstance& instance) : instance{instance} {}

    Colouring get_colouring() const;
    NewColourAssignments complete_colouring(Colouring& c, const TabuList *const tabu_list, VertexSortingCriterion crit = VertexSortingCriterion::COLOUR_DEGREE_ASC) const;
    NewColourAssignments complete_colouring(Colouring& c) const;
};

#endif //HYBRID_ALNS_GREEDYCOLOUR_H
