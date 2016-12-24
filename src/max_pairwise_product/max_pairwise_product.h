/*
 * max_pairwise_product.h
 *
 *  Created on: Dec 24, 2016
 *      Author: marcos
 */

#pragma once

#include <iostream>
#include <vector>

namespace mjlopez {
namespace algorithms {

template<typename InputType=int, typename ProductType=int, typename OperationCounter=int>
std::pair<ProductType,OperationCounter> max_pairwise_product(const std::vector<InputType>& numbers) {
  std::pair<ProductType, OperationCounter> result_pair(0, 0);
  size_t n = numbers.size();
  if (n == 1)
    return std::pair<ProductType,OperationCounter>(numbers.front(), static_cast<OperationCounter>(1));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      ++result_pair.second;
      if (numbers[i] * numbers[j] > result_pair.first) {
        result_pair.first = numbers[i] * numbers[j];
      }
    }
  }
  return result_pair;
}

} // namespace mjlopez
} // namespace algorithms



