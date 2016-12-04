//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_SOLUTION_H
#define HYBRID_ALNS_SOLUTION_H

#include "Column.h"

struct Solution {
    virtual ~Solution() {}
    virtual Solution* clone() const = 0;
    virtual float obj_value() const = 0;
    virtual void print_summary() const = 0;
    virtual std::vector<Column> to_columns() const = 0;
    virtual void from_columns(const std::vector<Column>& columns) = 0;

};

#endif //HYBRID_ALNS_SOLUTION_H
