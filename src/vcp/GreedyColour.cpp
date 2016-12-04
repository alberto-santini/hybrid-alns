//
// Created by alberto on 24/11/16.
//

#include "GreedyColour.h"

Colouring GreedyColour::get_colouring() const {
    Colouring c{instance};
    complete_colouring(c);
    return c;
}

GreedyColour::NewColourAssignments GreedyColour::complete_colouring(Colouring& c, const TabuList *const tabu_list, VertexSortingCriterion crit) const {
    NewColourAssignments nca;

    assert(c.is_partial());
    __attribute__((unused)) auto n_uncoloured_vertices = c.uncoloured.size();

    while(c.is_partial()) {
        switch(crit) {
            case VertexSortingCriterion::DEGREE_ASC:
                std::sort(c.uncoloured.begin(), c.uncoloured.end(), [this] (const Vertex& v, const Vertex& w) { return boost::out_degree(v, instance.g) < boost::out_degree(w, instance.g); });
                break;
            case VertexSortingCriterion::DEGREE_DESC:
                std::sort(c.uncoloured.begin(), c.uncoloured.end(), [this] (const Vertex& v, const Vertex& w) { return boost::out_degree(v, instance.g) > boost::out_degree(w, instance.g); });
                break;
            case VertexSortingCriterion::COLOUR_DEGREE_ASC:
                std::sort(c.uncoloured.begin(), c.uncoloured.end(), [&c] (const Vertex& v, const Vertex& w) { return c.colour_degree_of(v) < c.colour_degree_of(w); });
                break;
            case VertexSortingCriterion::COLOUR_DEGREE_DESC:
                std::sort(c.uncoloured.begin(), c.uncoloured.end(), [&c] (const Vertex& v, const Vertex& w) { return c.colour_degree_of(v) > c.colour_degree_of(w); });
                break;
        }

        Vertex v = c.uncoloured.front();
        std::vector<uint32_t> forbidden_for_this_vertex{};

        if(tabu_list != nullptr) {
            for(auto move : *tabu_list) {
                auto vc_move = static_cast<const VCTabuMove*>(move);
                if(vc_move->vertex == v) { forbidden_for_this_vertex.push_back(vc_move->colour); }
            }
        }

        auto new_colour = c.colour(c.uncoloured.front(), forbidden_for_this_vertex);
        nca.emplace(v, new_colour);
    }

    assert(c.uncoloured.size() == 0);
    assert(nca.size() == n_uncoloured_vertices);

    return nca;
}

GreedyColour::NewColourAssignments GreedyColour::complete_colouring(Colouring& c) const {
    return complete_colouring(c, nullptr);
}
