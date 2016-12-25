/*
 * random_generator.h
 *
 *  Created on: Dec 24, 2016
 *      Author: marcos
 */

#pragma once

#include <random>

namespace mjlopez {
namespace algorithms {

template<class IntType=int>
class random_generator {
public:
  random_generator(IntType min, IntType max)
  :_random_device(),
   _generator(),
   _unif_dist(min, max) {}

  IntType generate() {
    return _unif_dist(_generator);
  }
private:
  std::random_device _random_device;
  std::mt19937 _generator;
  std::uniform_int_distribution<IntType> _unif_dist;
};
} /* namespace algorithms */
} /* namespace mjlopez */

