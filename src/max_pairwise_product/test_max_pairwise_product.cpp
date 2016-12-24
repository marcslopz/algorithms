#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

#include "max_pairwise_product.h"

namespace ma = mjlopez::algorithms;

namespace {
template<class IntType=int>
class random_generator {
public:
  random_generator(IntType min, IntType max)
  :_random_device(),
   _generator(_random_device()),
   _unif_dist(min, max) {}

  IntType generate() {
    return _unif_dist(_generator);
  }
private:
  std::random_device _random_device;
  std::mt19937 _generator;
  std::uniform_int_distribution<IntType> _unif_dist;
};

void assert(bool condition) {
  if (!condition)
    throw 666;
}
void
test_trivial_cases() {
  /// empty vector
  const std::vector<int> empty_vector = {};
  const auto result_empty_vector = ma::max_pairwise_product(empty_vector);
  assert(result_empty_vector.first == 0);

  /// one-component vector
  const int component_one = 1;
  const int component_five = 5;
  std::vector<int> one_component_vector = {component_one};
  auto result_one_component_vector = ma::max_pairwise_product(one_component_vector);
  assert(result_one_component_vector.first == component_one);
  one_component_vector = {component_five};
  result_one_component_vector = ma::max_pairwise_product(one_component_vector);
  assert(result_one_component_vector.first == component_five);

  /// two-component vector
  const std::vector<int> two_component_vector = {component_one, component_five};
  const auto result_two_component_vector = ma::max_pairwise_product(two_component_vector);
  assert(result_two_component_vector.first == component_one * component_five);
}

void
test_easy_case() {
  /// n-component vector
  const std::vector<int> easy_vector = {1, 7, 5, 15, 7, 10};
  const auto result_easy_vector = ma::max_pairwise_product(easy_vector);
  assert(result_easy_vector.first == 15 * 10);
}

void
test_large_case() {
  std::vector<uint32_t> large_vector;
  random_generator<uint32_t> random_generator(0, 2e5);
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "starting generation";
  auto before = std::chrono::system_clock::now();
  const size_t vector_size = static_cast<size_t>(1e5);
  for (std::uint64_t i = 0; i < vector_size; ++i) {
    large_vector.push_back(random_generator.generate());
    if (i % 1000 == 0)
      std::cout << "." << std::flush;
  }
  auto after = std::chrono::system_clock::now();
  std::cout << "generated OK" << std::endl
      << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(after-before).count() << " seconds." << std::endl
      << std::endl
      << "Starting to calculate max_pairwise_product...";
  before = std::chrono::system_clock::now();
  const auto result_large_vector = ma::max_pairwise_product<uint32_t,uint64_t, uint64_t>(large_vector);
  after = std::chrono::system_clock::now();
  std::cout << "generated OK" << std::endl
      << "Result: " << result_large_vector.first << std::endl
      << "Operations: " << result_large_vector.second << std::endl
      << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(after-before).count() << " seconds." << std::endl
      << std::endl;
}
} // namespace

int main(int argc, char** argv) {
  try {
    test_trivial_cases();
    test_easy_case();
    test_large_case();
  } catch (...) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
