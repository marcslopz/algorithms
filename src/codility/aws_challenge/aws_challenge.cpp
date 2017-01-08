/*
 * light_chains.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include "aws_challenge.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

namespace ma = mjlopez::algorithms;


bool ma::apply_rule(std::string& s, size_t position) {
  const std::array<std::pair<std::string,std::string>,6> valid_rules({
    std::make_pair(std::string("AB"), std::string("AA")),
    std::make_pair(std::string("BA"), std::string("AA")),
    std::make_pair(std::string("CB"), std::string("CC")),
    std::make_pair(std::string("BC"), std::string("CC")),
    std::make_pair(std::string("AA"), std::string("A")),
    std::make_pair(std::string("CC"), std::string("C")),
  });
  for (const auto& rule: valid_rules) {
    if (s.compare(position, 2, rule.first) == 0) {
      s.replace(position, 2, rule.second);
      return true;
    }
  }
  return false;
}
std::string ma::string_transformation(const std::string& input) {
  std::string result = input;
  const size_t input_size = input.size();
  if (input_size <= 1)
    return result;  /// no rules matching 0 or 1-sized string
  size_t position = 0;
  size_t result_size = input_size - 1;
  while (position < result_size) {
    if (apply_rule(result, position)) {
      result_size = result.size();
    } else {
      ++position;
    }
  }
  return result;
}

enum class movement_type {
  up = 0,
  right = 1,
  down = 2,
  left = 3,
  min = up,
  max = left
};

int as_int(movement_type m) {
  return static_cast<int>(m);
}
std::vector<std::pair<int,int>> ma::calculate_spiral_points(int n) {
//  int pos = 0;
  std::pair<int,int> point(std::make_pair(0,0));
  std::vector<std::pair<int,int>> result({point});

  int movements = 0;
  while (result.size() < n) {
    for (int movement = as_int(movement_type::min); movement <= as_int(movement_type::max); ++movement) {
      if (movement == as_int(movement_type::up) or movement == as_int(movement_type::down))
        ++movements;
      for (int i = 0; i < movements; ++i) {
//        ++pos;
        switch (static_cast<movement_type>(movement)) {
        case (movement_type::up):
            ++point.second;
            break;
        case (movement_type::right):
            ++point.first;
            break;
        case (movement_type::down):
            --point.second;
            break;
        case (movement_type::left):
            --point.first;
            break;
        }
        result.push_back(point);
      }
    }
  }

  return result;
}

int ma::calculate_position_in_spiral(int x, int y) {
  int pos = 0;
  if (x == 0 and y == 0)
    return 0;

  std::pair<int,int> point(std::make_pair(0,0));
//  std::vector<std::pair<int,int>> result({point});

  int movements = 0;
  while (true) {
    for (int movement = as_int(movement_type::min); movement <= as_int(movement_type::max); ++movement) {
      if (movement == as_int(movement_type::up) or movement == as_int(movement_type::down))
        ++movements;
      for (int i = 0; i < movements; ++i) {
        switch (static_cast<movement_type>(movement)) {
        case (movement_type::up):
            ++point.second;
            break;
        case (movement_type::right):
            ++point.first;
            break;
        case (movement_type::down):
            --point.second;
            break;
        case (movement_type::left):
            --point.first;
            break;
        }
        ++pos;
        if (point.first == x and point.second == y)
          return pos;
      }
    }
  }
}

int ma::calculate_position_in_spiral_enh(int x, int y) {
  if (x == 0 and y == 0)
    return 0;
  int max_xy = std::max(x,y);
  int min_xy = std::min(x,y);
  int max_abs_minmax = std::max(std::abs(max_xy), std::abs(min_xy));
  int combination_members = 0;
  if (max_abs_minmax == std::abs(max_xy)) {
    if (max_xy >= 0) {
      combination_members = 2 * (max_xy - 1);
    } else {
      combination_members = 2 * (max_xy - 1) + 1;
    }
  } else {
    if (min_xy >= 0) {
      combination_members = 2 * (min_xy - 1);
    } else {
      combination_members = 2 * (min_xy - 1) + 1;
    }
  }
  std::cout << "combination_members: " << combination_members << std::endl;
  int pos = combination_members * combination_members +
      std::abs(x-y);
  return pos;
}

