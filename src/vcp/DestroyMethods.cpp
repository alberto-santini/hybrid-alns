//
// Created by alberto on 24/11/16.
//

#include "DestroyMethods.h"

Colouring* EmptySmallestColour::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto smallest_it = std::min_element(newc->colours.begin(), newc->colours.end(),
        [] (const auto& col1, const auto& col2) { return col1.size() < col2.size(); }
    );
    auto vertices_to_remove = *smallest_it;

    for(auto v : vertices_to_remove) { newc->uncolour(v); }
    return newc;
}

Colouring* EmptyNSmallestColours::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    std::vector<std::size_t> colour_ids(newc->colours.size());
    std::iota(colour_ids.begin(), colour_ids.end(), 0u);
    std::sort(colour_ids.begin(), colour_ids.end(),
        [&newc] (auto c1, auto c2) { return newc->colours[c1].size() < newc->colours[c2].size(); }
    );

    auto remove_max = static_cast<std::size_t>((colour_ids.size() - 1) * instance.vcparams.max_fraction_of_colours_to_empty_at_once);
    auto dis = std::uniform_int_distribution<std::size_t>(0, remove_max);
    auto remove_up_to = dis(*mt);
    auto vertices_to_remove = std::vector<Colouring::Vertex>{};

    for(auto i = 0u; i <= remove_up_to; ++i) {
        vertices_to_remove.insert(vertices_to_remove.end(), newc->colours[colour_ids[i]].begin(), newc->colours[colour_ids[i]].end());
    }

    for(auto v : vertices_to_remove) { newc->uncolour(v); }
    return newc;
}

Colouring* EmptySmallestColourRouletteWheel::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    std::vector<uint32_t> degrees(newc->colours.size());

    for(auto i = 0u; i < newc->colours.size(); ++i) {
        degrees[i] = newc->colours[i].size();
    }

    auto colour_id = degrees.size();
    auto degree_sum = std::accumulate(degrees.begin(), degrees.end(), 0u);

    std::uniform_int_distribution<uint32_t> dist(0, degree_sum);
    uint32_t degree_random = dist(*mt);
    uint32_t degree_accum = 0u;

    for(auto i = 0u; i < degrees.size(); ++i) {
        degree_accum += degrees[i];
        if(degree_accum >= degree_random) { colour_id = i; break; }
    }
    auto vertices_to_remove = newc->colours[colour_id];

    for(auto v : vertices_to_remove) { newc->uncolour(v); }
    return newc;
}

Colouring* EmptyRandomColour::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto dist = std::uniform_int_distribution<std::size_t>(0, newc->colours.size() - 1);
    auto vertices_to_remove = *(newc->colours.begin() + dist(*mt));

    for(auto v : vertices_to_remove) { newc->uncolour(v); }
    return newc;
}

Colouring* EmptyNRandomColours::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    std::vector<std::size_t> colour_ids(newc->colours.size());
    std::iota(colour_ids.begin(), colour_ids.end(), 0u);
    std::shuffle(colour_ids.begin(), colour_ids.end(), *mt);

    assert(instance.vcparams.max_fraction_of_colours_to_empty_at_once >= 0.0f);
    assert(instance.vcparams.max_fraction_of_colours_to_empty_at_once <= 1.0f);
    assert(colour_ids.size() >= 1u);

    auto remove_max = static_cast<std::size_t>((colour_ids.size() - 1) * instance.vcparams.max_fraction_of_colours_to_empty_at_once);
    auto dis = std::uniform_int_distribution<std::size_t>(0u, remove_max);
    auto remove_up_to = dis(*mt);
    auto vertices_to_remove = std::vector<Colouring::Vertex>{};

    for(auto i = 0u; i <= remove_up_to; ++i) {
        vertices_to_remove.insert(vertices_to_remove.end(), newc->colours[colour_ids[i]].begin(), newc->colours[colour_ids[i]].end());
    }

    for(auto v : vertices_to_remove) { newc->uncolour(v); }
    return newc;
}


Colouring* EmptyColourWithSmallestColourDegree::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto colour_id = 0u;
    auto degree = newc->total_colour_degree_of(0u);

    for(auto i = 1u; i < newc->colours.size(); ++i) {
        auto degree_i = newc->total_colour_degree_of(i);
        if(degree_i < degree) { colour_id = i; degree = degree_i; }
    }
    auto vertices_to_remove = newc->colours[colour_id];

    for(auto v : vertices_to_remove) { newc->uncolour(v); }
    return newc;
}

Colouring* EmptyNColoursWithSmallestColourDegree::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    std::vector<std::size_t> colour_ids(newc->colours.size());
    std::iota(colour_ids.begin(), colour_ids.end(), 0u);
    std::sort(colour_ids.begin(), colour_ids.end(),
        [&newc] (auto c1, auto c2) { return newc->total_colour_degree_of(c1) < newc->total_colour_degree_of(c2); }
    );

    assert(instance.vcparams.max_fraction_of_colours_to_empty_at_once >= 0.0f);
    assert(instance.vcparams.max_fraction_of_colours_to_empty_at_once <= 1.0f);
    assert(colour_ids.size() >= 1u);

    auto remove_max = static_cast<std::size_t>((colour_ids.size() - 1) * instance.vcparams.max_fraction_of_colours_to_empty_at_once);
    auto dis = std::uniform_int_distribution<std::size_t>(0, remove_max);
    auto remove_up_to = dis(*mt);
    auto vertices_to_remove = std::vector<Colouring::Vertex>{};

    for(auto i = 0u; i <= remove_up_to; ++i) {
        vertices_to_remove.insert(vertices_to_remove.end(), newc->colours[colour_ids[i]].begin(), newc->colours[colour_ids[i]].end());
    }

    for(auto v : vertices_to_remove) { newc->uncolour(v); }
    return newc;
}

Colouring* EmptyColourWithSmallestColourDegreeRouletteWheel::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    std::vector<uint32_t> degrees(newc->colours.size());
    uint32_t max_degree = 0u;

    for(auto i = 0u; i < newc->colours.size(); ++i) {
        degrees[i] = newc->total_colour_degree_of(i);
        if(degrees[i] > max_degree) { max_degree = degrees[i]; }
    }

    for(auto i = 0u; i < newc->colours.size(); ++i) {
        degrees[i] = max_degree - degrees[i];
    }

    auto colour_id = degrees.size();
    auto degree_sum = std::accumulate(degrees.begin(), degrees.end(), 0u);

    std::uniform_int_distribution<uint32_t> dist(0, degree_sum);
    uint32_t degree_random = dist(*mt);
    uint32_t degree_accum = 0u;

    for(auto i = 0u; i < degrees.size(); ++i) {
        degree_accum += degrees[i];
        if(degree_accum >= degree_random) { colour_id = i; break; }
    }
    auto vertices_to_remove = newc->colours[colour_id];

    for(auto v : vertices_to_remove) { newc->uncolour(v); }
    return newc;
}

Colouring* RemoveRandomVertexFromRandomColour::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto dist = std::uniform_int_distribution<std::size_t>(0, newc->colours.size() - 1);
    auto colour_it = newc->colours.begin() + dist(*mt);
    auto dist2 = std::uniform_int_distribution<std::size_t>(0, colour_it->size() - 1);

    newc->uncolour(*(colour_it->begin() + dist2(*mt)));
    return newc;
}

Colouring* RemoveRandomVertexFromSmallestColour::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto smallest_it = std::min_element(newc->colours.begin(), newc->colours.end(),
        [] (const auto& col1, const auto& col2) { return col1.size() < col2.size(); }
    );
    auto dist = std::uniform_int_distribution<std::size_t>(0, smallest_it->size() - 1);

    newc->uncolour(*(smallest_it->begin() + dist(*mt)));
    return newc;
}

Colouring* RemoveRandomVertexFromBiggestColour::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto biggest_it = std::max_element(newc->colours.begin(), newc->colours.end(),
        [] (const auto& col1, const auto& col2) { return col1.size() < col2.size(); }
    );
    auto dist = std::uniform_int_distribution<std::size_t>(0, biggest_it->size() - 1);

    newc->uncolour(*(biggest_it->begin() + dist(*mt)));
    return newc;
}

Colouring* UncolourVertexWithSmallestDegree::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto iters = boost::vertices(instance.g);
    auto v = std::min_element(iters.first, iters.second,
        [this] (const auto& v1, const auto& v2) { return boost::out_degree(v1, instance.g) < boost::out_degree(v2, instance.g); }
    );

    newc->uncolour(*v);
    return newc;
}

Colouring* UncolourVertexWithSmallestColourDegree::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto iters = boost::vertices(instance.g);
    auto v = std::min_element(iters.first, iters.second,
        [&newc] (const auto& v1, const auto& v2) { return newc->colour_degree_of(v1) < newc->colour_degree_of(v2); }
    );

    newc->uncolour(*v);
    return newc;
}

Colouring* UncolourVertexWithSmallestColourDegreeRouletteWheel::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    std::vector<uint32_t> degrees(instance.num_vertices);
    uint32_t max_degree = 0u;

    for(auto v = 0u; v < instance.num_vertices; ++v) {
        degrees[v] = newc->colour_degree_of(v);
        if(degrees[v] > max_degree) { max_degree = degrees[v]; }
    }

    for(auto v = 0u; v < instance.num_vertices; ++v) {
        degrees[v] = max_degree - degrees[v];
    }

    auto vertex_id = degrees.size();
    auto degree_sum = std::accumulate(degrees.begin(), degrees.end(), 0u);

    std::uniform_int_distribution<uint32_t> dist(0, degree_sum);
    uint32_t degree_random = dist(*mt);
    uint32_t degree_accum = 0u;

    for(auto v = 0u; v < degrees.size(); ++v) {
        degree_accum += degrees[v];
        if(degree_accum >= degree_random) { vertex_id = v; break; }
    }

    newc->uncolour(vertex_id);
    return newc;
}

Colouring* UncolourVertexWithLargestDegree::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto iters = boost::vertices(instance.g);
    auto v = std::max_element(iters.first, iters.second,
        [this] (const auto& v1, const auto& v2) { return boost::out_degree(v1, instance.g) < boost::out_degree(v2, instance.g); }
    );

    newc->uncolour(*v);
    return newc;
}

Colouring* UncolourVertexWithLargestColourDegree::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    auto iters = boost::vertices(instance.g);
    auto v = std::max_element(iters.first, iters.second,
        [&newc] (const auto& v1, const auto& v2) { return newc->colour_degree_of(v1) < newc->colour_degree_of(v2); }
    );

    newc->uncolour(*v);
    return newc;
}

Colouring* UncolourVertexWithLargestColourDegreeRouletteWheel::operator()(const Solution *const solution) const {
    const Colouring *const c = static_cast<const Colouring *const>(solution);
    assert(!c->is_partial());

    Colouring* newc = new Colouring{*c};
    std::vector<uint32_t> degrees(instance.num_vertices);

    for(auto v = 0u; v < instance.num_vertices; ++v) {
        degrees[v] = newc->colour_degree_of(v);
    }

    auto vertex_id = degrees.size();
    auto degree_sum = std::accumulate(degrees.begin(), degrees.end(), 0u);

    std::uniform_int_distribution<uint32_t> dist(0, degree_sum);
    uint32_t degree_random = dist(*mt);
    uint32_t degree_accum = 0u;

    for(auto v = 0u; v < degrees.size(); ++v) {
        degree_accum += degrees[v];
        if(degree_accum >= degree_random) { vertex_id = v; break; }
    }

    newc->uncolour(vertex_id);
    return newc;
}