//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_SOLUTION_H
#define HYBRID_ALNS_SOLUTION_H

#include "Instance.h"

class Solution {
    const Instance const* instance;

public:

    Solution(const Instance const* instance) : instance{instance} {}
};

#endif //HYBRID_ALNS_SOLUTION_H
