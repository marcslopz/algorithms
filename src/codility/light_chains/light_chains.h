/*
 * light_chains.h
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#pragma once

#include <utility>
#include <string>

namespace mjlopez {
namespace algorithms {

std::pair<int,int>  /// first=result, second=number of operations
number_of_valid_chains(const std::string&);

bool
is_valid_chain(const std::string& s, size_t start, size_t size, int& total_operations);

} /* namespace algorithms */
} /* namespace mjlopez */

