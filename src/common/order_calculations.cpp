#include <cmath>
#include <iostream>

#include "order_calculations.h"

namespace ma = mjlopez::algorithms;

std::string
ma::calculate_order(
    const std::pair<size_t,uint64_t> first_step,
    const std::pair<size_t,uint64_t> second_step) {
  const uint operations_ratio = second_step.second / first_step.second;

  /// O(1)
  const uint constant_thres = 1;
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "actual ops ratio: " << operations_ratio << std::endl
      << "constant_thres: " << constant_thres << std::endl;
  if (operations_ratio <= constant_thres)
    return order_text.at(static_cast<size_t>(order::constant));

  /// O(n)
  const size_t size_ratio = second_step.first / first_step.first;
  const uint n_thres = size_ratio;
  std::cout << "n_thres: " << n_thres << std::endl;
  if (operations_ratio <= size_ratio)
    return order_text.at(static_cast<size_t>(order::n));

  /// O(nlogn)
  const uint nlogn_thres =
      size_ratio * (log(size_ratio) / log(first_step.first) + 1) + 1;
  std::cout << "nlogn_thres: " << nlogn_thres << std::endl;
  if (operations_ratio <= nlogn_thres)
    return order_text.at(static_cast<size_t>(order::nlogn));

  /// O(n2)
  const uint n2_thres = size_ratio * size_ratio;
  std::cout << "n2_thres: " << n2_thres << std::endl;
  if (operations_ratio <= n2_thres)
    return order_text.at(static_cast<size_t>(order::n2));

  /// O(n2logn)
  const uint n2logn_thres =
      size_ratio * size_ratio * (log(size_ratio) / log(first_step.first) + 1) + 1;
  std::cout << "n2logn_thres: " << n2logn_thres << std::endl;
  if (operations_ratio <= n2logn_thres)
    return order_text.at(static_cast<size_t>(order::n2logn));

  /// O(n3)
  const uint n3_thres = size_ratio * size_ratio * size_ratio;
  std::cout << "n3_thres: " << n3_thres << std::endl;
  if (operations_ratio <= n3_thres)
    return order_text.at(static_cast<size_t>(order::n3));

  /// O(greater than n3)
  return order_text.at(static_cast<size_t>(order::greater_than_n3));
}
