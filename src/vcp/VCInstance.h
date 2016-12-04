//
// Created by alberto on 23/11/16.
//

#ifndef HYBRID_ALNS_VCINSTANCE_H
#define HYBRID_ALNS_VCINSTANCE_H

#include <string>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "VCParams.h"

struct VCInstance {
    using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
    using Vertex = boost::graph_traits<Graph>::vertex_descriptor;
    using Edge = boost::graph_traits<Graph>::edge_descriptor;

    VCParams vcparams;
    uint32_t num_vertices;
    uint32_t num_edges;
    Graph g;

    VCInstance(std::string instance_filename, std::string params_filename);
};

#endif //HYBRID_ALNS_VCINSTANCE_H
