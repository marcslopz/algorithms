#include <array>
#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

#include "max_pairwise_product.h"
#include "common/order_calculations.h"
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
  auto result_empty_vector = ma::max_pairwise_product(empty_vector);
  assert(result_empty_vector.first == 0);
  result_empty_vector = ma::max_pairwise_product_enhanced(empty_vector);
  assert(result_empty_vector.first == 0);

  /// one-component vector
  const int component_one = 1;
  const int component_five = 5;
  std::vector<int> one_component_vector = {component_one};
  auto result_one_component_vector = ma::max_pairwise_product(one_component_vector);
  assert(result_one_component_vector.first == 0);
  result_one_component_vector = ma::max_pairwise_product_enhanced(one_component_vector);
  assert(result_one_component_vector.first == 0);
  one_component_vector = {component_five};
  result_one_component_vector = ma::max_pairwise_product(one_component_vector);
  assert(result_one_component_vector.first == 0);
  result_one_component_vector = ma::max_pairwise_product_enhanced(one_component_vector);
  assert(result_one_component_vector.first == 0);

  /// two-component vector
  const std::vector<int> two_component_vector = {component_one, component_five};
  auto result_two_component_vector = ma::max_pairwise_product(two_component_vector);
  assert(result_two_component_vector.first == component_one * component_five);
  result_two_component_vector = ma::max_pairwise_product_enhanced(two_component_vector);
  assert(result_two_component_vector.first == component_one * component_five);
}

void
test_easy_case() {
  /// n-component vector
  const std::vector<int> easy_vector = {1, 7, 5, 15, 7, 10};
  auto result_easy_vector = ma::max_pairwise_product(easy_vector);
  assert(result_easy_vector.first == 15 * 10);
  result_easy_vector = ma::max_pairwise_product_enhanced(easy_vector);
  assert(result_easy_vector.first == 15 * 10);
}

template<typename Content, typename Size>
std::vector<Content>
generate_input(const Size& size, const Content& min, const Content& max) {
  std::vector<uint32_t> large_vector;
  ma::random_generator<uint32_t> random_generator(min, max);
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "starting generation";
  auto before = std::chrono::system_clock::now();
  for (std::uint64_t i = 0; i < size; ++i) {
    large_vector.push_back(random_generator.generate());
    if (i % 1000 == 0)
      std::cout << "." << std::flush;
  }
  auto after = std::chrono::system_clock::now();
  std::cout << "generated OK" << std::endl
      << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(after-before).count() << " seconds." << std::endl
      << std::endl;
  return large_vector;
}
uint64_t
test_large_case(uint64_t vector_size, bool enhanced) {
  std::vector<uint32_t> large_vector = generate_input<uint32_t,uint64_t>(vector_size, 0, 2e5);
  std::cout << "Starting to calculate max_pairwise_product...";
  auto before = std::chrono::system_clock::now();
  std::pair<uint32_t,uint64_t> result_large_vector;
  if (enhanced)
    result_large_vector = ma::max_pairwise_product_enhanced<uint32_t,uint64_t, uint64_t>(large_vector);
  else
    result_large_vector = ma::max_pairwise_product<uint32_t,uint64_t, uint64_t>(large_vector);
  auto after = std::chrono::system_clock::now();
  std::cout << "generated OK" << std::endl
      << "Result: " << result_large_vector.first << std::endl
      << "Operations: " << result_large_vector.second << std::endl
      << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(after-before).count() << " seconds." << std::endl
      << std::endl;
  return result_large_vector.second;
}

void
test_large_case() {
  std::pair<size_t,size_t> input_sizes(1e4,1e5);
  std::pair<size_t,uint64_t> number_of_ops;

  bool enhanced = false;
  number_of_ops.first = test_large_case(input_sizes.first, enhanced);
  number_of_ops.second = test_large_case(input_sizes.second, enhanced);
  ma::order actual_order = ma::calculate_order(input_sizes, number_of_ops);
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "enhanced: " << std::boolalpha << enhanced << std::endl
      << "first input size: " << input_sizes.first << std::endl
      << "second input size: " << input_sizes.second << std::endl
      << "first number of ops: " << number_of_ops.first << std::endl
      << "second number of ops: " << number_of_ops.second << std::endl
      << "order of algorithm: " << ma::as_string(actual_order) << std::endl;
  assert(actual_order == ma::order::n2);

  enhanced = true;
  number_of_ops.first = test_large_case(input_sizes.first, enhanced);
  number_of_ops.second = test_large_case(input_sizes.second, enhanced);
  actual_order = ma::calculate_order(input_sizes, number_of_ops);
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "enhanced: " << std::boolalpha << enhanced << std::endl
      << "first input size: " << input_sizes.first << std::endl
      << "second input size: " << input_sizes.second << std::endl
      << "first number of ops: " << number_of_ops.first << std::endl
      << "second number of ops: " << number_of_ops.second << std::endl
      << "order of algorithm: " << ma::as_string(actual_order) << std::endl;
  assert(actual_order == ma::order::nlogn);
}

void
test_compare_algorithms() {
  const uint64_t size = 5;
  const uint32_t min_value = 0;
  const uint32_t max_value = 2e5;
  const auto input = generate_input<uint32_t,uint64_t>(size, min_value, max_value);
  const auto result = ma::max_pairwise_product<uint32_t,uint64_t,uint64_t>(input);
  const auto result_enhanced = ma::max_pairwise_product_enhanced<uint32_t,uint64_t,uint64_t>(input);
  std::cout << "-----------------------------" << std::endl
      << __func__ << std::endl
      << "input vector: [";
  for (const auto i: input) {
    std::cout << i << ", ";
  }
  std::cout << "]" << std::endl
      << "max_pairwise_product's result: " << result.first << std::endl
      << "max_pairwise_product enhanced's result: " << result_enhanced.first << std::endl;
  assert(result.first == result_enhanced.first);
  std::cout << "Assert OK!" << std::endl
      << "-----------------------------" << std::endl;
}
} // namespace

int main(int argc, char** argv) {
  try {
    test_trivial_cases();
    test_easy_case();
    test_large_case();
    test_compare_algorithms();
  } catch (...) {
    std::cerr << "TEST FAILURE!!!!" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
