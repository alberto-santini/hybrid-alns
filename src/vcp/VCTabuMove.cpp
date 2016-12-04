//
// Created by alberto on 29/11/16.
//

#include "VCTabuMove.h"

std::ostream& VCTabuMove::format(std::ostream& out) const {
    out << "{v: " << vertex << ", c: " << colour << "} tabu until iter " << valid_until;
    return out;
}