/*
 * light_chains.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include <cstddef>
#include <cstdlib>
#include <limits>

#include "tape_equilibrium.h"

namespace ma = mjlopez::algorithms;

int ma::tape_equilibrium(const std::vector<int>& input) {
  int sum = 0;
  for (const auto& el: input) {
    sum += el;
  }
  const size_t input_size = input.size();
  int min_difference = std::numeric_limits<int>::max();
  for (size_t i = 0; i < input_size - 1; ++i) {
    /// sum = A[N-1] + .. + A[i+1] - A[i] - ... - A[0]
    /// P = i + 1
    sum -= 2 * input[i];
    if (std::abs(sum) < min_difference)
      min_difference = std::abs(sum);
  }
  return min_difference;
}
