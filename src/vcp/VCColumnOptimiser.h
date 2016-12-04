//
// Created by alberto on 04/12/16.
//

#ifndef HYBRID_ALNS_VCCOLUMNOPTIMISER_H
#define HYBRID_ALNS_VCCOLUMNOPTIMISER_H


#include "../ColumnOptimiser.h"
#include "VCInstance.h"
#include "Colouring.h"

struct VCColumnOptimiser : public ColumnOptimiser {
    const VCInstance& instance;

    VCColumnOptimiser(const VCInstance& instance) : instance{instance} {}
    Colouring* optimise(const ColumnPool& columns) const;
};


#endif //HYBRID_ALNS_VCCOLUMNOPTIMISER_H
