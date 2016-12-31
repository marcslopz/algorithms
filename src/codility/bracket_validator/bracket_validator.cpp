/*
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include "bracket_validator.h"

namespace ma = mjlopez::algorithms;

int
ma::count_largest_bracket_slice(const std::string& input, size_t start, size_t end) {
  if (start == end)
    return 0; /// valid empty string (base case)

  size_t next_start = input.find("(", start, end - start + 1);
  if (next_start == std::string::npos)
    return -1;

}
