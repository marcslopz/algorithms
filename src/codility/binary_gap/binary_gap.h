/*
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#pragma once

#include <iostream>
#include <string>

namespace mjlopez {
namespace algorithms {

class result_class {
public:
  int result;
  bool is_left;
  bool is_right;
  result_class(int result, bool is_left, bool is_right)
  : result(result),
    is_left(is_left),
    is_right(is_right) {}
};

int binary_gap(int N);
bool is_a_zero(int N, int position);
result_class binary_gap_enh(int N, int start, int end);
bool is_all_zeros(int N, int start, int end);
bool is_all_ones(int N, int start, int end);


} /* namespace algorithms */
} /* namespace mjlopez */

std::ostream& operator<<(std::ostream& o, const mjlopez::algorithms::result_class& c);
