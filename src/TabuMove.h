//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_TABUMOVE_H
#define HYBRID_ALNS_TABUMOVE_H

#include <cstdint>
#include <vector>

struct TabuMove {
    const uint32_t valid_until;
    TabuMove(uint32_t valid_until) : valid_until{valid_until} {}
};

using TabuList = std::vector<const TabuMove const*>;

#endif //HYBRID_ALNS_TABUMOVE_H
