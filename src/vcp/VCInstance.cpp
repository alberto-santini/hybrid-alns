//
// Created by alberto on 23/11/16.
//

#include <fstream>
#include <iostream>
#include "VCInstance.h"

VCInstance::VCInstance(std::string instance_filename, std::string params_filename) : vcparams{params_filename} {
    std::ifstream gfile(instance_filename, std::ios_base::in);

    gfile >> num_vertices >> num_edges;

    for(auto v = 0u; v < num_vertices; ++v) {
        boost::add_vertex(g);
    }

    for(auto e = 0u; e < num_edges; ++e) {
        auto src = 0u;
        auto trg = 0u;

        gfile >> src >> trg;

        assert(src < num_vertices);
        assert(trg < num_vertices);

        auto v = boost::vertex(src, g);
        auto w = boost::vertex(trg, g);

        boost::add_edge(v, w, g);
    }
}
