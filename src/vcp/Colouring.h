//
// Created by alberto on 23/11/16.
//

#ifndef HYBRID_ALNS_COLOURING_H
#define HYBRID_ALNS_COLOURING_H

#include <iostream>
#include "../Solution.h"
#include "../PartialSolution.h"
#include "VCInstance.h"

struct Colouring : public PartialSolution, public Solution {
    using Vertex = VCInstance::Vertex;
    using Colour = std::vector<Vertex>;

    const VCInstance& instance;
    std::vector<Colour> colours;
    std::vector<int64_t> rev_colours;
    std::vector<Vertex> uncoloured;

    Colouring(const VCInstance& instance);
    Colouring(const Colouring& other);
    ~Colouring() {}

    void operator=(const Colouring& other);
    void print_summary() const;
    Solution* clone() const;
    std::vector<Column> to_columns() const;
    void from_columns(const std::vector<Column>& columns);

    float obj_value() const;
    void colour(Vertex v, uint32_t colour);
    void uncolour(Vertex v);
    bool can_colour(Vertex v, uint32_t colour);
    bool is_coloured(Vertex v) const;
    bool is_partial() const;
    bool is_valid() const;
    uint32_t new_colour_for(Vertex v);
    uint32_t colour_of(Vertex v) const;
    uint32_t colour_degree_of(Vertex v) const;
    uint32_t total_colour_degree_of(const std::vector<Vertex>& colour) const;
    uint32_t total_colour_degree_of(uint32_t colour_id) const;
    uint32_t colour(Vertex v);
    uint32_t colour(Vertex v, const std::vector<uint32_t>& forbidden_colours);
    std::set<std::set<Vertex>> colours_as_sets() const;

    bool operator==(const Colouring& other) const;
};

inline std::ostream& operator<<(std::ostream& out, const Colouring& c) {
    for(auto coln = 0u; coln < c.colours.size(); ++coln) {
        out << "Colour " << coln << ": { ";
        for(auto v : c.colours[coln]) { out << v << " "; }
        out << "}" << std::endl;
    }
    out << "Uncoloured: { ";
    for(auto v : c.uncoloured) { out << v << " "; }
    out << "}" << std::endl;
    return out;
}

#endif //HYBRID_ALNS_COLOURING_H
