/*
 * light_chains.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include <iostream>
#include <sstream>
#include <vector>

#include "light_chains.h"

namespace ma = mjlopez::algorithms;

std::pair<int, uint64_t>  /// first=result, second=number of operations
ma::number_of_valid_chains(const std::string& s) {
  const size_t s_size = s.size();
  auto result = std::make_pair(0, static_cast<uint64_t>(0));
  for (size_t start = 0; start < s_size; ++start) { /// start position of subchains
    for (size_t size = 1; size <= s_size - start; ++size) { /// size of subchains
      if (is_valid_chain(s, start, size, result.second)) {
        ++result.first;
      }
    }
  }
  return result;
}

namespace {
std::string as_string(const std::vector<int>& v) {
  std::ostringstream oss;
  oss << "[";
  for (const auto& i: v) {
    oss << i << ", ";
  }
  oss << "]";
  return oss.str();
}
}
std::pair<int, uint64_t>  /// first=result, second=number of operations
ma::number_of_valid_chains_enh(const std::string& s) {
  const size_t s_size = s.size();
  auto result = std::make_pair(0, static_cast<uint64_t>(0));

  std::vector<int> digit_counter(10, 0);
  int number_of_pairs = 0;

  for (size_t i = 0; i < s_size; ++i) {
    std::cout << "#1 i=" << i << ", number_of_pairs=" << number_of_pairs << std::endl;
    add_to_digit_counter(digit_counter, s[i] - '0', number_of_pairs,
        result.second);
    int anagram_of_palindrome_threshold = (i + 1) / 2;
    if (number_of_pairs == anagram_of_palindrome_threshold)
      ++result.first;
    std::cout << "#2 i=" << i << ", number_of_pairs=" << number_of_pairs << ", anagram_of_palindrome_threshold="
        << anagram_of_palindrome_threshold << ", result.first=" << result.first << ", s[i]=" << (s[i] - '0')
        << ", digit_counter=" << as_string(digit_counter) << std::endl;
    int temp_number_of_pairs = number_of_pairs;
    auto temp_digit_counter(digit_counter);
    result.second += 13;
    for (size_t j = 0; j < i; ++j) {
      std::cout << "#3 i=" << i << ", j=" << j << ", temp_number_of_pairs=" << temp_number_of_pairs << std::endl;
      remove_from_digit_counter(temp_digit_counter, s[j] - '0',
          temp_number_of_pairs, result.second);
      anagram_of_palindrome_threshold = (i - j) / 2;
      if (temp_number_of_pairs == anagram_of_palindrome_threshold)
        ++result.first;
      result.second += 3;
      std::cout << "#4 i=" << i << ", j=" << j << ", temp_number_of_pairs=" << temp_number_of_pairs << ", anagram_of_palindrome_threshold="
          << anagram_of_palindrome_threshold << ", result.first=" << result.first << ", s[i]=" << (s[i] - '0')
          << ", temp_digit_counter=" << as_string(temp_digit_counter) << std::endl;
    }
  }

  return result;
}

bool ma::is_valid_chain(const std::string& s, size_t start, size_t size,
    uint64_t& total_operations) {
  std::vector<int> counter(10, 0);
  uint64_t operations = 0;
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
  return number_of_pairs == size / 2;
}

void ma::add_to_digit_counter(std::vector<int>& digit_counter, int digit,
    int& number_of_pairs, uint64_t& operations) {
  ++digit_counter[digit];
  if (digit_counter[digit] % 2 == 0) {
    ++number_of_pairs;
    ++operations;
  }
  operations += 2;
}

void ma::remove_from_digit_counter(std::vector<int>& digit_counter, int digit,
    int& number_of_pairs, uint64_t& operations) {
  --digit_counter[digit];
  if (digit_counter[digit] % 2 != 0) {
    --number_of_pairs;
    ++operations;
  }
  operations += 2;
}
