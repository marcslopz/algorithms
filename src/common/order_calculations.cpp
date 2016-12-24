#include <cmath>
#include <iostream>

#include "order_calculations.h"

namespace ma = mjlopez::algorithms;

ma::order
ma::calculate_order(
    const std::pair<size_t,size_t> input_sizes,
    const std::pair<uint64_t,uint64_t> number_of_ops) {
  if (input_sizes.second <= input_sizes.first)
    throw 666;
  if (number_of_ops.second <= number_of_ops.first)
      throw 666;
  const uint operations_ratio = number_of_ops.second / number_of_ops.first;

  /// O(1)
  const uint constant_thres = 1;
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "actual ops ratio: " << operations_ratio << std::endl
      << "constant_thres: " << constant_thres << std::endl;
  if (operations_ratio <= constant_thres)
    return order::constant;

  /// O(n)
  const size_t size_ratio = input_sizes.second / input_sizes.first;
  const uint n_thres = size_ratio;
  std::cout << "n_thres: " << n_thres << std::endl;
  if (operations_ratio <= size_ratio)
    return order::n;

  /// O(nlogn)
  const uint nlogn_thres =
      size_ratio * (log(size_ratio) / log(input_sizes.first) + 1) + 1;
  std::cout << "nlogn_thres: " << nlogn_thres << std::endl;
  if (operations_ratio <= nlogn_thres)
    return order::nlogn;

  /// O(n2)
  const uint n2_thres = size_ratio * size_ratio;
  std::cout << "n2_thres: " << n2_thres << std::endl;
  if (operations_ratio <= n2_thres)
    return order::n2;

  /// O(n2logn)
  const uint n2logn_thres =
      size_ratio * size_ratio * (log(size_ratio) / log(input_sizes.first) + 1) + 1;
  std::cout << "n2logn_thres: " << n2logn_thres << std::endl;
  if (operations_ratio <= n2logn_thres)
    return order::n2logn;

  /// O(n3)
  const uint n3_thres = size_ratio * size_ratio * size_ratio;
  std::cout << "n3_thres: " << n3_thres << std::endl;
  if (operations_ratio <= n3_thres)
    return order::n3;

  /// O(greater than n3)
  return order::greater_than_n3;
}

std::string
ma::as_string(ma::order my_order) {
  return ma::order_text.at(static_cast<size_t>(my_order));
}
