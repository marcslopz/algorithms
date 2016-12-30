/*
 * test.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include <iostream>
#include <string>
#include <vector>

#include "light_chains.h"
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
  const std::string empty_string = {};
  auto result_empty_string = ma::number_of_valid_chains(empty_string);
  assert(result_empty_string.first == 0);

  /// one-component vector
  const char component_one = '1';
  const char component_five = '5';
  std::string one_component_string = {component_one};
  auto result_one_component_string = ma::number_of_valid_chains(one_component_string);
  assert(result_one_component_string.first == 1);
  one_component_string = {component_five};
  result_one_component_string = ma::number_of_valid_chains(one_component_string);
  assert(result_one_component_string.first == 0);

  /// two-component vector
  std::string two_component_string = {component_one, component_five};
  auto result_two_component_string = ma::number_of_valid_chains(two_component_string);
  assert(result_two_component_string.first == 2);
  two_component_string = {component_one, component_one};
  result_two_component_string = ma::number_of_valid_chains(two_component_string);
  assert(result_two_component_string.first == 3);
}

void
test_easy_case() {
  /// n-component vector
  const std::vector<std::pair<std::string,int>> easy_vectors(
      {std::make_pair(std::string("0123456789"),10),
    std::make_pair(std::string("02002"), 11),
    std::make_pair(std::string("12321"), 7),
    std::make_pair(std::string("11223"), 12)});
  for (const auto& p: easy_vectors) {
    const auto result_easy_vector = ma::number_of_valid_chains(p.first);
    assert(result_easy_vector.first == p.second);
  }
}

/**
template<typename Content, typename Size>
std::vector<Content>
generate_input(const Size& size, ma::random_generator<Content>& random_generator) {
  std::vector<uint32_t> large_vector;
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
  ma::random_generator<uint32_t> random_generator(0, 2e5);
  std::vector<uint32_t> large_vector = generate_input<uint32_t,uint64_t>(vector_size, random_generator);
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
  const size_t number_of_generations = 10;
  using size_type = uint64_t;
  using product_type = uint64_t;
  using operations_type = uint64_t;
  using element_type = uint32_t;
  ma::random_generator<size_type> random_size_generator(2, 1e5);
  ma::random_generator<element_type> random_element_generator(0, 2e5);
  for (size_t i = 0; i < number_of_generations; ++i) {
    const auto size = random_size_generator.generate();
    const auto input = generate_input<element_type,size_type>(size, random_element_generator);
    const auto result = ma::max_pairwise_product<element_type,product_type,operations_type>(input);
    const auto result_enhanced = ma::max_pairwise_product_enhanced<element_type,product_type,operations_type>(input);
    std::cout << "-----------------------------" << std::endl
        << __func__ << std::endl
        << "size: " << size  << std::endl
        << "input vector: [";
    for (size_t j = 0; j < size; ++j) {
      if (j == 0)
        std::cout << input [j] << " ";
      if (j == 0 and size > 1)
        std::cout << "... ";
      if (j == size - 1)
        std::cout << input[j];
    }
    std::cout << "]" << std::endl
        << "max_pairwise_product's result: " << result.first << std::endl
        << "max_pairwise_product enhanced's result: " << result_enhanced.first << std::endl;
    assert(result.first == result_enhanced.first);
    std::cout << "Assert OK!" << std::endl
        << "-----------------------------" << std::endl;
  }
}
*/
} // namespace

int main(int argc, char** argv) {
  try {
    test_trivial_cases();
    test_easy_case();
    /*
    test_large_case();
    test_compare_algorithms();
    */
  } catch (...) {
    std::cerr << "TEST FAILURE!!!!" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}



