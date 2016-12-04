//
// Created by alberto on 04/12/16.
//

#ifndef HYBRID_ALNS_COLUMNOPTIMISER_H
#define HYBRID_ALNS_COLUMNOPTIMISER_H


#include "Column.h"
#include "Solution.h"

struct ColumnOptimiser {
    uint32_t timeout;

    void set_timeout(uint32_t timeout) { this->timeout = timeout; }
    virtual Solution* optimise(const ColumnPool& columns) const = 0;
};


#endif //HYBRID_ALNS_COLUMNOPTIMISER_H
