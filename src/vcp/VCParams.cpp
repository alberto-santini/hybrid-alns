//
// Created by alberto on 01/12/16.
//

#include "VCParams.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

VCParams::VCParams(std::string filename) {
    boost::property_tree::ptree tree;
    boost::property_tree::read_json(filename, tree);

    max_fraction_of_colours_to_empty_at_once = tree.get<float>("max_fraction_of_colours_to_empty_at_once");

    assert(max_fraction_of_colours_to_empty_at_once >= 0.0f);
    assert(max_fraction_of_colours_to_empty_at_once <= 1.0f);
}
