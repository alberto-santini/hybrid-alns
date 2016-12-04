//
// Created by Alberto Santini on 18/11/2016.
//

#include "Params.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

Params::Params(std::string filename) {
    boost::property_tree::ptree tree;
    boost::property_tree::read_json(filename, tree);

    initial_destroy_score = tree.get<float>("initial_destroy_score");
    initial_repair_score = tree.get<float>("initial_repair_score");
    new_best_score_update = tree.get<float>("new_best_score_update");
    improves_current_score_update = tree.get<float>("improves_current_score_update");
    accepted_score_update = tree.get<float>("accepted_score_update");
    rejected_score_update = tree.get<float>("rejected_score_update");
    tabu_tenure = tree.get<uint32_t>("tabu_tenure");
    alns_iterations = tree.get<uint32_t>("alns_iterations");
    column_optimisation_frequency = tree.get<uint32_t>("column_optimisation_frequency");
    column_optimisation_timeout = tree.get<uint32_t>("column_optimisation_timeout");
}
