//
// Created by alberto on 03/12/16.
//

#ifndef HYBRID_ALNS_COLUMN_H
#define HYBRID_ALNS_COLUMN_H

#include <cstdint>
#include <vector>
#include <numeric>
#include <unordered_set>

struct ColumnHash {
    std::size_t operator()(const std::vector<uint32_t>& v) const {
        return std::accumulate(v.begin(), v.end(), 0u,
            [] (std::size_t cur_hash, uint32_t value) { return cur_hash ^ (static_cast<std::size_t>(value) + 0x9e3779b9 + (cur_hash<<6) + (cur_hash>>2)); }
        );
    }
};

using Column = std::vector<uint32_t>;
using ColumnPool = std::unordered_set<Column, ColumnHash>;

#endif //HYBRID_ALNS_COLUMN_H
