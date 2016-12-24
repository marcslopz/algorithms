/*
 * merge_sort.h
 *
 *  Created on: Dec 24, 2016
 *      Author: marcos
 */

#pragma once

#include <cstddef>
#include <utility>
#include <vector>

namespace mjlopez {
namespace algorithms {

template<typename InputType=int, typename ProductType=int, typename OperationCounter=int>
std::pair<ProductType,OperationCounter> max_pairwise_product_enhanced(const std::vector<InputType>& numbers) {
  const std::pair<const std::vector<InputType>,OperationCounter> sorted_result = merge_sort(numbers);
  std::pair<ProductType, OperationCounter> result_pair(0, 0);
  result_pair.second = ++sorted_result.second;
  const std::vector<InputType>& sorted_vector = sorted_result.first;
  result_pair.first = sorted_vector[sorted_vector.size()-1] * sorted_vector[sorted_vector.size()-2];
  return result_pair;
}

template<typename InputType=int, typename OperationCounter=int>
const std::pair<std::vector<InputType>,OperationCounter>
merge(
    const std::pair<std::vector<InputType>,OperationCounter>& first,
    const std::pair<std::vector<InputType>,OperationCounter>& second) {
  OperationCounter merge_ops = 0;
  const std::vector<InputType>& first_vector = first.first;
  const std::vector<InputType>& second_vector = second.first;
  const size_t merged_size = first_vector.size() + second_vector.size();
  size_t first_position = 0;
  size_t second_position = 0;
  std::pair<std::vector<InputType>,OperationCounter> result;
  std::vector<InputType>& result_vector = result.first;
  for (size_t result_position = 0; result_position < merged_size; ++result_position) {
    ++merge_ops;
    if (first_position == first_vector.size()) {
      result_vector.push_back(second_vector[second_position]);
      ++second_position;
    } else if (second_position == second_vector.size()) {
      result_vector.push_back(first_vector[first_position]);
      ++first_position;
    } else if (first_vector[first_position] <= second_vector[second_position]) {
      result_vector.push_back(first_vector[first_position]);
      ++first_position;
    } else {
      result_vector.push_back(second_vector[second_position]);
      ++second_position;
    }
  }
  result.second = merge_ops + first.second + second.second;
  return result;
}

template<typename InputType=int, typename OperationCounter=int>
const std::pair<std::vector<InputType>,OperationCounter>
merge_sort(const std::vector<InputType>& numbers, size_t start, size_t length) {
  /// base case
  if (length <= 1) {
    return std::make_pair(std::vector<InputType>(numbers.begin() + start, numbers.begin() + start + length), 1);
  }
  const size_t middle = start + length / 2;
  const auto first_half_result = merge_sort(numbers, start, middle - start);
  const auto second_half_result = merge_sort(numbers, middle, start + length - middle);
  return merge(first_half_result, second_half_result);
}

} /* namespace algorithms */
} /* namespace mjlopez */

