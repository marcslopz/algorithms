/*
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include <iostream>
using std::cout;
using std::endl;

#include "binary_gap.h"

namespace ma = mjlopez::algorithms;

bool ma::is_a_zero(int N, int position) {
  return (N >> position & 1) == 0;
}
int ma::binary_gap(int N) {
  int result = 0;
  int temp_result = 0;

  const int size_of_int = sizeof(int) * 8;

//  cout << "------------------- N: " << N << endl;
  /// remove most significative zeros
//  cout << "Start to remove left-side zeros..." << endl;
  int i = size_of_int - 1;
  for (; i >= 0; --i) {
    if (!is_a_zero(N, i)) {
//      cout << "i: " << i << ", is_a_zero: no" << endl;
      break;
    } else {
//      cout << "i: " << i << ", is_a_zero: yes" << endl;
    }
  }
//  cout << "Finished OK, most significant bit at position: " << i << endl;

  /// count length of binary gaps and keep the maximum
  for (int j = i; j >= 0; --j) {
    if (!is_a_zero(N, j)) {
//      cout << "i: " << i << ", is_a_zero: no, temp_result: " << temp_result
//          << ", result(before): " << result;
      if (temp_result > result)
        result = temp_result;
//      cout << ", result(after): " << result << endl;
      temp_result = 0;
    } else {
      ++temp_result;
//      cout << "i: " << i << ", is_a_zero: yes, temp_result: " << temp_result
//          << endl;
    }
  }
//  cout << "------------------- N: " << N << ", result: " << result << endl;

  return result;
}

bool ma::is_all_zeros(int N, int start, int end) {
  int N_shifted = N >> (sizeof(int)*8 - 1 - end);
  uint mask = 0;
  mask = ~mask;
  mask = mask >> (sizeof(int)*8 - 1 - (end - start));
  cout << "----------------------" << __func__ << "(" << start << ", " << end << ")" << endl
      << "N_shifted: " << N_shifted << endl
      << "mask: " << mask << endl
      << "(N_shifted & mask): " << (N_shifted & mask) << endl
      << "(N_shifted & mask) == 0: " << std::boolalpha << ((N_shifted & mask) == 0) << endl
      << "----------------------" << __func__ << "(" << start << ", " << end << ")" << endl;
  return (N_shifted & mask) == 0;
}

bool ma::is_all_ones(int N, int start, int end) {
  int N_shifted = N >> (sizeof(int)*8 - 1 - end);
  uint mask = 0;
  mask = ~mask;
  mask = mask >> (sizeof(int)*8 - 1 - (end - start));
  cout << "----------------------" << __func__ << "(" << start << ", " << end << ")" << endl
      << "N_shifted: " << N_shifted << endl
      << "mask: " << mask << endl
      << "(N_shifted & mask): " << (N_shifted & mask) << endl
      << "(N_shifted & mask) == mask: " << std::boolalpha << ((N_shifted & mask) == mask) << endl
      << "----------------------" << __func__ << "(" << start << ", " << end << ")" << endl;
  return (N_shifted & mask) == mask;
}

ma::result_class ma::binary_gap_enh(int N, int start, int end) {
  cout << "STARTING: start: " << start << ", end: " << end << endl;

  if (is_all_ones(N, start, end)) {
    cout << "BASE CASE #0: start: " << start << ", end: " << end << ", result: " << ma::result_class(0, false, false) << endl;
    return ma::result_class(0, false, false);
  }
  if (is_all_zeros(N, start, end)) {
    if (start == 0 or end == (sizeof(int) * 8 - 1)) {
      cout << "BASE CASE #1: start: " << start << ", end: " << end << ", result: " << ma::result_class(0, false, false) << endl;
      return ma::result_class(0, false, false);
    } else {
      cout << "BASE CASE #2: start: " << start << ", end: " << end << ", result: " << ma::result_class(end - start + 1, true, true) << endl;
      return ma::result_class(end - start + 1, true, true);
    }
  }

  const int middle = start + (end - start) / 2;
  const auto right_result = binary_gap_enh(N, middle + 1, end);
  const auto left_result = binary_gap_enh(N, start, middle);

  if (right_result.result == 0) {
    cout << "ENDING: start: " << start << ", end: " << end << ", result: " << ma::result_class(left_result.result, left_result.is_left, false) << endl;
    return ma::result_class(left_result.result, left_result.is_left, false);
  }
  if (left_result.result == 0) {
    cout << "ENDING: start: " << start << ", end: " << end << ", result: " << ma::result_class(right_result.result, false, right_result.is_right) << endl;
    return ma::result_class(right_result.result, false, right_result.is_right);
  }
  if (right_result.is_left and left_result.is_right) {
    cout << "ENDING: start: " << start << ", end: " << end << ", result: " << ma::result_class(right_result.result + left_result.result, left_result.is_left, right_result.is_right) << endl;
    return ma::result_class(right_result.result + left_result.result, left_result.is_left, right_result.is_right);
  }
  if (right_result.result > left_result.result) {
    cout << "ENDING: start: " << start << ", end: " << end << ", result: " << ma::result_class(right_result.result, false, right_result.is_right) << endl;
    return ma::result_class(right_result.result, false, right_result.is_right);
  } else {
    cout << "ENDING: start: " << start << ", end: " << end << ", result: " << ma::result_class(left_result.result, left_result.is_left, false) << endl;
    return ma::result_class(left_result.result, left_result.is_left, false);
  }
}

std::ostream& operator<<(std::ostream& o, const ma::result_class& c) {
  o << "{result: " << c.result << ", is_left: " << std::boolalpha << c.is_left
      << ", is_right: " << c.is_right << "}";
  return o;
}
