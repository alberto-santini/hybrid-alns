//
// Created by alberto on 01/12/16.
//

#include "MWSS.h"
#include "../SuppressOutput.h"

MWSS::Colour MWSS::largest_stable_set_for(const std::vector<MWSS::Vertex>& vertices) const {
    assert(!vertices.empty());

    MWSSgraph m_graph;
    MWSSdata m_data;
    wstable_info m_info;
    wstable_parameters m_params;

    auto solution = Colour{};
    auto m_weight_lower_bound = 1;
    auto m_weight_goal = MWISNW_MAX;
    int m_graph_allocated = 0, m_initialised = 0, m_called = 0;

    reset_pointers(&m_graph, &m_data, &m_info);
    default_parameters(&m_params);

    m_graph_allocated = allocate_graph(&m_graph, vertices.size());
    MWIScheck_rval(m_graph_allocated, "Cannot allocate m_graph");

    m_graph.n_nodes = vertices.size();

    for(auto i = 1; i <= m_graph.n_nodes; i++) {
        m_graph.weight[i] = 1;
        for(auto j = 1; j <= m_graph.n_nodes; j++) { m_graph.adj[i][j] = 0; }
    }

    for(auto i = 0u; i < vertices.size(); ++i) {
        for(auto j = i + 1; j < vertices.size(); ++j) {
            if(boost::edge(vertices[i], vertices[j], instance.g).second) {
                m_graph.adj[i + 1][j + 1] = 1;
                m_graph.adj[j + 1][i + 1] = 1;
            }
        }
    }

    build_graph(&m_graph);
    assert(check_graph(&m_graph) == 1);

    m_initialised = initialize_max_wstable(&m_graph, &m_info);
    MWIScheck_rval(m_initialised, "Cannot initialise max wstable");

    SUPPRESS_OUTPUT(m_called = call_max_wstable(&m_graph, &m_data, &m_params, &m_info, m_weight_goal, m_weight_lower_bound);)

    if(m_called == 0) {
        for(auto i = 1; i <= m_data.n_best; i++) {
            if(m_data.best_sol[i] != NULL) {
                solution.push_back(vertices[m_data.best_sol[i]->name - 1]);
            }
        }
    }

    CLEANUP: free_max_wstable(&m_graph, &m_data, &m_info);

    return solution;
}

std::vector<MWSS::Colour> MWSS::all_stable_sets_for(const std::vector<MWSS::Vertex>& vertices) const {
    assert(!vertices.empty());

    auto solution = std::vector<Colour>{};
    auto vertices_to_add = vertices;

    while(!vertices_to_add.empty()) {
        auto sset = largest_stable_set_for(vertices_to_add);
        assert(!sset.empty());

        solution.push_back(sset);

        auto it = std::remove_if(vertices_to_add.begin(), vertices_to_add.end(),
            [&sset] (const auto& v) { return std::find(sset.begin(), sset.end(), v) != sset.end(); }
        );
        vertices_to_add.erase(it, vertices_to_add.end());
    }

    assert(!solution.empty());
    return solution;
}
