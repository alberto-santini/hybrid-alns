//
// Created by alberto on 24/11/16.
//

#include "WorseAccept.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

WorseAccept::WorseAccept(std::string acceptance_params_filename, const Params& alns_params) : AcceptanceCriterion{alns_params}, dis{0.0f, 1.0f} {
    boost::property_tree::ptree tree;
    boost::property_tree::read_json(acceptance_params_filename, tree);

    start_probability = tree.get<float>("worse_accept.start_probability");
}

bool WorseAccept::operator()(const Solution *const incumbent, const Solution *const current, const Solution *const best, uint32_t iteration_number) const {
    if(incumbent->obj_value() <= current->obj_value()) { return true; }
    assert(mt != nullptr);
    return dis(*mt) < start_probability * static_cast<float>(iteration_number) / static_cast<float>(alns_params.alns_iterations);
}