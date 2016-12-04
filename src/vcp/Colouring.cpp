//
// Created by alberto on 23/11/16.
//

#include "Colouring.h"

Colouring::Colouring(const VCInstance& instance) : instance{instance} {
    rev_colours = std::vector<int64_t>(instance.num_vertices, -1);
    uncoloured = std::vector<Vertex>(instance.num_vertices);
    std::iota(uncoloured.begin(), uncoloured.end(), 0u);
}

float Colouring::obj_value() const {
    assert(uncoloured.empty());
    return colours.size();
}

uint32_t Colouring::new_colour_for(Colouring::Vertex v) {
    assert(v < rev_colours.size());
    assert(rev_colours[v] < 0);

    auto it = std::find(uncoloured.begin(), uncoloured.end(), v);
    assert(it != uncoloured.end());

    colours.push_back({v});
    rev_colours[v] = colours.size() - 1;
    uncoloured.erase(it);

    return colours.size() - 1;
}

void Colouring::colour(Colouring::Vertex v, uint32_t colour) {
    assert(v < rev_colours.size());
    assert(colour < colours.size());
    assert(rev_colours[v] < 0);

    auto it = std::find(uncoloured.begin(), uncoloured.end(), v);
    assert(it != uncoloured.end());

    colours[colour].push_back(v);
    rev_colours[v] = colour;
    uncoloured.erase(it);
}

void Colouring::uncolour(Colouring::Vertex v) {
    assert(v < rev_colours.size());

    auto c = rev_colours[v];
    assert(c >= 0);
    assert(static_cast<uint32_t>(c) < colours.size());

    auto it = std::find(colours[c].begin(), colours[c].end(), v);
    assert(it != colours[c].end());

    uncoloured.push_back(v);
    colours[c].erase(it);
    rev_colours[v] = -1;

    if(colours[c].empty()) {
        for(auto v = 0u; v < instance.num_vertices; ++v) {
            if(rev_colours[v] > c) { --rev_colours[v]; }
        }
        colours.erase(colours.begin() + c);
    }
}

bool Colouring::is_coloured(Colouring::Vertex v) const {
    assert(v < rev_colours.size());
    return rev_colours[v] >= 0;
}

uint32_t Colouring::colour_of(Colouring::Vertex v) const {
    assert(v < rev_colours.size());
    return rev_colours[v];
}

bool Colouring::is_partial() const {
    return !uncoloured.empty();
}

uint32_t Colouring::colour_degree_of(Colouring::Vertex v) const {
    uint32_t degree = 0u;

    for(auto it = boost::out_edges(v, instance.g); it.first != it.second; ++it.first) {
        auto w = boost::target(*it.first, instance.g);
        if(is_coloured(w)) { ++degree; }
    }

    return degree;
}

uint32_t Colouring::colour(Colouring::Vertex v) {
    return colour(v, std::vector<uint32_t>{});
}

uint32_t Colouring::colour(Colouring::Vertex v, const std::vector<uint32_t>& forbidden_colours) {
    for(auto i = 0u; i < colours.size(); ++i) {
        if(std::find(forbidden_colours.begin(), forbidden_colours.end(), i) != forbidden_colours.end()) { continue; }
        if(can_colour(v, i)) { colour(v, i); return i; }
    }
    new_colour_for(v);
    return colours.size() - 1;
}

bool Colouring::can_colour(Colouring::Vertex v, uint32_t colour) {
    assert(colour < colours.size());

    for(auto w : colours[colour]) {
        if(boost::edge(v, w, instance.g).second) { return false; }
    }

    return true;
}

void Colouring::operator=(const Colouring& other) {
    assert(&instance == &(other.instance));

    colours = other.colours;
    rev_colours = other.rev_colours;
    uncoloured = other.uncoloured;
}

Colouring::Colouring(const Colouring& other) : instance{other.instance} {
    *this = other;
}

Solution* Colouring::clone() const {
    return static_cast<Solution*>(new Colouring(*this));
}

bool Colouring::is_valid() const {
    if(is_partial()) { return false; }
    for(auto c = 0u; c < colours.size(); ++c) {
        for(auto it1 = colours[c].begin(); it1 < colours[c].end(); ++it1) {
            for(auto it2 = it1 + 1; it2 < colours[c].end(); ++it2) {
                if(boost::edge(*it1, *it2, instance.g).second) { return false; }
            }
        }
    }
    return true;
}

uint32_t Colouring::total_colour_degree_of(uint32_t colour_id) const {
    return total_colour_degree_of(colours[colour_id]);
}

uint32_t Colouring::total_colour_degree_of(const std::vector<Colouring::Vertex>& colour) const {
    uint32_t total = 0u;
    for(const auto& v : colour) { total += colour_degree_of(v); }
    return total;
}

void Colouring::print_summary() const {
    std::cout << colours.size() << " colours" << std::endl;
}

bool Colouring::operator==(const Colouring& other) const {
    if(colours.size() != other.colours.size()) { return false; }
    if(uncoloured.size() != other.uncoloured.size()) { return false; }
    if(uncoloured != other.uncoloured) { return false; }
    return colours_as_sets() == other.colours_as_sets();
}

std::set<std::set<Colouring::Vertex>> Colouring::colours_as_sets() const {
    auto s = std::set<std::set<Colouring::Vertex>>{};

    for(const auto& col : colours) {
        s.insert(std::set<Vertex>(col.begin(), col.end()));
    }

    return s;
}

std::vector<Column> Colouring::to_columns() const {
    auto columns = std::vector<Column>{};

    for(const auto& colour : colours) {
        columns.push_back(std::vector<uint32_t>(instance.num_vertices, 0u));
        for(auto v : colour) {
            columns.back()[v] = 1u;
        }
    }

    return columns;
}

void Colouring::from_columns(const std::vector<Column>& columns) {
    *this = Colouring{instance};

    std::vector<uint32_t> coloured(instance.num_vertices, 0u);

    for(auto c = 0u; c < columns.size(); ++c) {
        int64_t colour_id = -1;

        for(auto v = 0u; v < columns[c].size(); ++v) {
            if(columns[c][v] > 0 && coloured[v] == 0u) {
                if(colour_id < 0) {
                    colour_id = new_colour_for(v);
                } else {
                    colour(v, colour_id);
                }
                coloured[v] = 1u;
            }
        }
    }

    assert(is_valid());
}
