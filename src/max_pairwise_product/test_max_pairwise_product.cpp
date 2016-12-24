#include <array>
#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

#include "max_pairwise_product.h"
#include "common/random_generator.h"

namespace ma = mjlopez::algorithms;

namespace {

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

uint64_t
test_large_case(uint64_t vector_size) {
  std::vector<uint32_t> large_vector;
  ma::random_generator<uint32_t> random_generator(0, 2e5);
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "starting generation";
  auto before = std::chrono::system_clock::now();
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
  return result_large_vector.second;
}

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

std::string
calculate_order(
    const std::pair<size_t,uint64_t> first_step,
    const std::pair<size_t,uint64_t> second_step) {
  const std::array<const char*, (static_cast<size_t>(order::max) - static_cast<size_t>(order::min) + 1)> order_text = {
      "greater_than_n3",
      "n3",
      "n2logn",
      "n2",
      "nlogn",
      "n",
      "constant"};

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

void
test_large_case() {
  std::pair<size_t,uint64_t> result_e4;
  std::pair<size_t,uint64_t> result_e5;
  result_e4.first = static_cast<size_t>(1e4);
  result_e5.first = static_cast<size_t>(1e5);
  result_e4.second = test_large_case(result_e4.first);
  result_e5.second = test_large_case(result_e5.first);

  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "first input size: " << result_e4.first << std::endl
      << "second input size: " << result_e5.first << std::endl
      << "first number of ops: " << result_e4.second << std::endl
      << "second number of ops: " << result_e5.second << std::endl
      << "order of algorithm: " << calculate_order(result_e4, result_e5) << std::endl;
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
