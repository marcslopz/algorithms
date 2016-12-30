/*
 * light_chains.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include <vector>

#include "light_chains.h"

namespace ma = mjlopez::algorithms;

std::pair<int,int>  /// first=result, second=number of operations
ma::number_of_valid_chains(const std::string& s) {
  const size_t s_size = s.size();
  auto result = std::make_pair(0,0);
  for (size_t start = 0; start < s_size; ++start) { /// start position of subchains
    for (size_t size = 1; size <= s_size - start; ++size) {  /// size of subchains
      if (is_valid_chain(s, start, size, result.second)) {
        ++result.first;
      }
    }
  }
  return result;
}

bool
ma::is_valid_chain(const std::string& s, size_t start, size_t size, int& total_operations) {
  std::vector<int> counter(10, 0);
  int operations = 0;
  for (size_t s_pos = start; s_pos < start + size; ++s_pos) {
    ++counter[s[s_pos] - '0'];
    ++operations;
  }
  int number_of_pairs = 0;
  for (size_t i = 0; i < 10; ++i) {
    number_of_pairs += counter[i] / 2;
    ++operations;
  }
  total_operations += operations;
  return number_of_pairs >= size / 2;
}
