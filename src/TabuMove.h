//
// Created by Alberto Santini on 18/11/2016.
//

#ifndef HYBRID_ALNS_TABUMOVE_H
#define HYBRID_ALNS_TABUMOVE_H

#include <cstdint>
#include <vector>
#include <iostream>

struct TabuMove {
    const uint32_t valid_until;

    TabuMove(uint32_t valid_until) : valid_until{valid_until} {}
    virtual ~TabuMove() {}
    virtual std::ostream& format(std::ostream& out) const = 0;
};

inline std::ostream& operator<<(std::ostream& out, const TabuMove& move) { return move.format(out); }

using TabuList = std::vector<const TabuMove*>;

#endif //HYBRID_ALNS_TABUMOVE_H
