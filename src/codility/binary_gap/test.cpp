/*
 * test.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "binary_gap.h"
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
  const std::vector<std::pair<int,int>> test_cases(
      {std::make_pair(1041,5),
      std::make_pair(15,0),
      std::make_pair(8,0),
      std::make_pair(1,0),
      std::make_pair(0,0)});
  for (const auto& p: test_cases) {
    const auto result = ma::binary_gap(p.first);
    assert(result == p.second);
  }
}
/*

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
*/

int
generate_input(ma::random_generator<int>& random_generator) {
  return random_generator.generate();
}
/*
uint64_t
test_large_case(size_t vector_size, bool enhanced) {
  ma::random_generator<int> random_generator(0, 9);
  const auto large_string = generate_input<size_t>(vector_size, random_generator);
  std::cout << "Starting to calculate number_of_valid_chains..." << std::endl;
  auto before = std::chrono::system_clock::now();
  const auto result_large_vector = enhanced ?
      ma::number_of_valid_chains_enh(large_string) :
      ma::number_of_valid_chains(large_string);
  auto after = std::chrono::system_clock::now();
  std::cout << "calculated OK" << std::endl
      << "Result: " << result_large_vector.first << std::endl
      << "Operations: " << result_large_vector.second << std::endl
      << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(after-before).count() << " seconds." << std::endl
      << std::endl;
  return result_large_vector.second;
}
void
test_large_case() {
  std::pair<size_t,size_t> input_sizes(100,1000);
  std::pair<uint64_t,uint64_t> number_of_ops;

  bool enhanced = false;
  number_of_ops.first = test_large_case(input_sizes.first, enhanced);
  number_of_ops.second = test_large_case(input_sizes.second, enhanced);
  ma::order actual_order = ma::calculate_order(input_sizes, number_of_ops);
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "enhanced: "  << std::boolalpha << enhanced << std::endl
      << "first input size: " << input_sizes.first << std::endl
      << "second input size: " << input_sizes.second << std::endl
      << "first number of ops: " << number_of_ops.first << std::endl
      << "second number of ops: " << number_of_ops.second << std::endl
      << "order of algorithm: " << ma::as_string(actual_order) << std::endl;
  assert(actual_order == ma::order::n3);

  enhanced = true;
  number_of_ops.first = test_large_case(input_sizes.first, enhanced);
  number_of_ops.second = test_large_case(input_sizes.second, enhanced);
  actual_order = ma::calculate_order(input_sizes, number_of_ops);
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "enhanced: "  << std::boolalpha << enhanced << std::endl
      << "first input size: " << input_sizes.first << std::endl
      << "second input size: " << input_sizes.second << std::endl
      << "first number of ops: " << number_of_ops.first << std::endl
      << "second number of ops: " << number_of_ops.second << std::endl
      << "order of algorithm: " << ma::as_string(actual_order) << std::endl;
  assert(actual_order == ma::order::n2);
}
void
test_compare_algorithms() {
  const size_t number_of_generations = 10;
  using size_type = int;
  using operations_type = uint64_t;
  using element_type = int;
  ma::random_generator<element_type> random_element_generator(0, 100);
  for (size_t i = 0; i < number_of_generations; ++i) {
    const auto input = generate_input(random_element_generator);
    std::cout << "-----------------------------" << std::endl
        << __func__ << std::endl
        << "input: " << input << std::endl;
    const auto result = ma::binary_gap(input);
    std::cout << "binary_gap's result: " << result << std::endl;

    auto result_enhanced = ma::binary_gap_enh(input, 0, 31);
    std::cout << "binary_gap_enh's result: " << result_enhanced.result << std::endl;
    assert(result == result_enhanced.result);
    std::cout << "Assert OK!" << std::endl
        << "-----------------------------" << std::endl;
  }
}
*/
} // namespace

int main(int argc, char** argv) {
  try {
    test_trivial_cases();
    /*
    test_easy_case();
    test_large_case();
    test_compare_algorithms();
    */
  } catch (...) {
    std::cerr << "TEST FAILURE!!!!" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "TEST OK" << std::endl;

  return EXIT_SUCCESS;
}



