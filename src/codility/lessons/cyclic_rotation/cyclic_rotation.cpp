/*
 * light_chains.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include <cstddef>

#include "cyclic_rotation.h"

namespace ma = mjlopez::algorithms;

std::vector<int> ma::cyclic_rotate(const std::vector<int>& A, int K) {
  const size_t v_size = A.size();
  std::vector<int> result(v_size);
  for (size_t i = 0; i < v_size; ++i) {
    result[(i + K) % v_size] = A[i];
  }
  return result;
}
