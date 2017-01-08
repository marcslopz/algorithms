/*
 * light_chains.h
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#pragma once

#include <string>
#include <vector>

namespace mjlopez {
namespace algorithms {

bool apply_rule(std::string& s, size_t position);

std::string string_transformation(const std::string&);

std::vector<std::pair<int,int>> calculate_spiral_points(int);

int calculate_position_in_spiral(int,int);

/// not working!!! (maybe someday...)
int calculate_position_in_spiral_enh(int,int);


} /* namespace algorithms */
} /* namespace mjlopez */

