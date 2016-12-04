//
// Created by alberto on 24/11/16.
//

#include "Colouring.h"
#include "RepairMethods.h"
#include "GreedyColour.h"
#include "MWSS.h"

Colouring* GreedyRecolourDegreeAsc::operator()(const PartialSolution *const partial_solution, uint32_t iter) {
    const Colouring *const c = static_cast<const Colouring *const>(partial_solution);
    assert(c->is_partial());

    Colouring* newc = new Colouring{*c};
    GreedyColour gc{instance};
    auto nca = gc.complete_colouring(*newc, tabu_list, GreedyColour::VertexSortingCriterion::DEGREE_ASC);

    for(auto vertex_colour : nca) {
        tabu_list->push_back(new VCTabuMove{vertex_colour.first, vertex_colour.second, iter + alns_params.tabu_tenure});
    }

    return newc;
}

Colouring* GreedyRecolourDegreeDesc::operator()(const PartialSolution *const partial_solution, uint32_t iter) {
    const Colouring *const c = static_cast<const Colouring *const>(partial_solution);
    assert(c->is_partial());

    Colouring* newc = new Colouring{*c};
    GreedyColour gc{instance};
    auto nca = gc.complete_colouring(*newc, tabu_list, GreedyColour::VertexSortingCriterion::DEGREE_DESC);

    for(auto vertex_colour : nca) {
        tabu_list->push_back(new VCTabuMove{vertex_colour.first, vertex_colour.second, iter + alns_params.tabu_tenure});
    }

    return newc;
}

Colouring* GreedyRecolourColourDegreeAsc::operator()(const PartialSolution *const partial_solution, uint32_t iter) {
    const Colouring *const c = static_cast<const Colouring *const>(partial_solution);
    assert(c->is_partial());

    Colouring* newc = new Colouring{*c};
    GreedyColour gc{instance};
    auto nca = gc.complete_colouring(*newc, tabu_list, GreedyColour::VertexSortingCriterion::COLOUR_DEGREE_ASC);

    for(auto vertex_colour : nca) {
        tabu_list->push_back(new VCTabuMove{vertex_colour.first, vertex_colour.second, iter + alns_params.tabu_tenure});
    }

    return newc;
}

Colouring* GreedyRecolourColourDegreeDesc::operator()(const PartialSolution *const partial_solution, uint32_t iter) {
    const Colouring *const c = static_cast<const Colouring *const>(partial_solution);
    assert(c->is_partial());

    Colouring* newc = new Colouring{*c};
    GreedyColour gc{instance};
    auto nca = gc.complete_colouring(*newc, tabu_list, GreedyColour::VertexSortingCriterion::COLOUR_DEGREE_DESC);

    for(auto vertex_colour : nca) {
        tabu_list->push_back(new VCTabuMove{vertex_colour.first, vertex_colour.second, iter + alns_params.tabu_tenure});
    }

    return newc;
}

Colouring* MWSSRecolour::operator()(const PartialSolution *const partial_solution, uint32_t iter) {
    const Colouring *const c = static_cast<const Colouring *const>(partial_solution);
    assert(c->is_partial());

    Colouring* newc = new Colouring{*c};
    MWSS mwss{instance};

    auto new_colours = mwss.all_stable_sets_for(newc->uncoloured);

    for(const auto& colour : new_colours) {
        assert(!colour.empty());

        auto c = newc->new_colour_for(colour[0]);
        tabu_list->push_back(new VCTabuMove{colour[0], c, iter + alns_params.tabu_tenure});

        for(auto c_id = 1u; c_id < colour.size(); ++c_id) {
            newc->colour(colour[c_id], c);
            tabu_list->push_back(new VCTabuMove{colour[c_id], c, iter + alns_params.tabu_tenure});
        }
    }

    assert(newc->is_valid());

    return newc;
}

Colouring* GreedyAndMWSSRecolour::operator()(const PartialSolution *const partial_solution, uint32_t iter) {
    const Colouring *const c = static_cast<const Colouring *const>(partial_solution);
    assert(c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto uncoloured = newc->uncoloured;

    for(auto v : uncoloured) {
        for(auto c = 0u; c < newc->colours.size(); ++c) {
            auto it = std::find_if(tabu_list->begin(), tabu_list->end(),
                [&v,&c] (const TabuMove* move) {
                    auto vcmove = static_cast<const VCTabuMove *const>(move);
                    return vcmove->vertex == v && vcmove->colour == c;
                }
            );

            if(it != tabu_list->end()) { continue; }

            if(newc->can_colour(v, c)) {
                newc->colour(v, c);
                tabu_list->push_back(new VCTabuMove{v, c, iter + alns_params.tabu_tenure});
                break;
            }
        }
    }

    if(!newc->is_partial()) { return newc; }

    MWSS mwss{instance};
    auto new_colours = mwss.all_stable_sets_for(newc->uncoloured);

    for(const auto& colour : new_colours) {
        assert(!colour.empty());

        auto c = newc->new_colour_for(colour[0]);
        tabu_list->push_back(new VCTabuMove{colour[0], c, iter + alns_params.tabu_tenure});

        for(auto c_id = 1u; c_id < colour.size(); ++c_id) {
            newc->colour(colour[c_id], c);
            tabu_list->push_back(new VCTabuMove{colour[c_id], c, iter + alns_params.tabu_tenure});
        }
    }

    assert(newc->is_valid());

    return newc;
}