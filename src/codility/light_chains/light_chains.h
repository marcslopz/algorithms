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

} /* namespace algorithms */
} /* namespace mjlopez */

