/*
 * order_calculations.h
 *
 *  Created on: Dec 24, 2016
 *      Author: marcos
 */

#pragma once

#include <array>
#include <string>

namespace mjlopez {
namespace algorithms {

enum class order {
  greater_than_n3,
  n3,
  n2logn,
  n2,
  nlogn,
  n,
  constant,
  min = greater_than_n3,
  max = constant
};

constexpr std::array<const char*,(static_cast<size_t>(order::max) - static_cast<size_t>(order::min) + 1)> order_text = {
    "greater_than_n3",
    "n3",
    "n2logn",
    "n2",
    "nlogn",
    "n",
    "constant"};

std::string
calculate_order(
    const std::pair<size_t,uint64_t> first_step,
    const std::pair<size_t,uint64_t> second_step);

} /* namespace algorithms */
} /* namespace mjlopez */
