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

std::pair<int, uint64_t>  /// first=result, second=number of operations
number_of_valid_chains(const std::string&);

std::pair<int, uint64_t>  /// first=result, second=number of operations
number_of_valid_chains_enh(const std::string&);

bool
is_valid_chain(const std::string& s, size_t start, size_t size,
    uint64_t& total_operations);

void
add_to_digit_counter(std::vector<int>& digit_counter, int digit,
    int& number_of_pairs, uint64_t& operations);

void remove_from_digit_counter(std::vector<int>& digit_counter, int digit,
    int& number_of_pairs, uint64_t& operations);

} /* namespace algorithms */
} /* namespace mjlopez */

