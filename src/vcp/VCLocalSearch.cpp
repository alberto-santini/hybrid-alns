//
// Created by alberto on 30/11/16.
//

#include "VCLocalSearch.h"

bool VCLocalSearch::try_to_colour(Colouring& colouring, Colouring::Vertex v) const {
    for(auto i = 0u; i < colouring.colours.size(); ++i) {
        if(colouring.can_colour(v, i)) {
            colouring.colour(v, i);
            return true;
        }
    }
    return false;
}

bool VCLocalSearch::try_harder_to_colour(Colouring& colouring, Colouring::Vertex v) const {
    for(auto i = 0u; i < colouring.colours.size(); ++i) {
        if(try_to_colour_and_replace(colouring, v, i)) { return true; }
    }
    return false;
}

void VCLocalSearch::operator()(Solution *const solution) const {
    Colouring newc = *static_cast<Colouring *const>(solution);

    auto smallest_it = std::min_element(newc.colours.begin(), newc.colours.end(),
        [] (const auto& c1, const auto& c2) { return c1.size() < c2.size(); }
    );
    auto remove = *smallest_it;
    for(auto v : remove) { newc.uncolour(v); }

    for(auto v : remove) {
        if(try_to_colour(newc, v) || try_harder_to_colour(newc, v)) { continue; }
        else { return; }
    }

    assert(newc.is_valid());

    *static_cast<Colouring *const>(solution) = newc;
}

bool VCLocalSearch::try_to_colour_and_replace(Colouring& colouring, Colouring::Vertex v, uint32_t c) const {
    assert(c < colouring.colours.size());

    using Vertex = Colouring::Vertex;
    std::vector<Vertex> to_replace;

    for(auto w : colouring.colours[c]) {
        if(boost::edge(v, w, colouring.instance.g).second) {
            to_replace.push_back(w);
        }
    }

    if(to_replace.size() == colouring.colours[c].size()) { return false; }

    std::map<Vertex, uint32_t> where_to_place;

    for(auto w : to_replace) {
        for(auto i = 0u; i < colouring.colours.size(); ++i) {
            if(i == c) { continue; }
            if(colouring.can_colour(w, i)) {
                where_to_place[w] = i;
                break;
            }
        }

        if(where_to_place.find(w) != where_to_place.end()) {
            continue;
        } else {
            return false;
        }
    }

    for(const auto& vc : where_to_place) {
        colouring.uncolour(vc.first);
        colouring.colour(vc.first, vc.second);
    }

    colouring.colour(v, c);

    return true;
}
