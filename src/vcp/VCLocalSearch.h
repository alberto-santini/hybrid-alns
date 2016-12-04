//
// Created by alberto on 30/11/16.
//

#ifndef HYBRID_ALNS_VCLOCALSEARCH_H
#define HYBRID_ALNS_VCLOCALSEARCH_H

#include "../LocalSearchOperator.h"
#include "Colouring.h"

struct VCLocalSearch : public LocalSearchOperator {
    void operator()(Solution *const solution) const;

private:
    bool try_to_colour(Colouring& colouring, Colouring::Vertex v) const;
    bool try_harder_to_colour(Colouring& colouring, Colouring::Vertex v) const;
    bool try_to_colour_and_replace(Colouring& colouring, Colouring::Vertex v, uint32_t c) const;
};

#endif //HYBRID_ALNS_VCLOCALSEARCH_H
