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

#include "common/order_calculations.h"
#include "common/random_generator.h"
#include "odd_occurrences.h"

namespace ma = mjlopez::algorithms;

namespace {
void assert(bool condition) {
  if (!condition)
    throw 666;
}
void
test_trivial_cases() {
//  [9, 3, 9, 3, 9, 7, 9]
  const std::vector<std::pair<std::vector<int>,int>> input({
    std::make_pair(std::vector<int>({9, 3, 9, 3, 9, 7, 9}), 7),
    std::make_pair(std::vector<int>({42}), 42)
  });
  for (const auto e: input) {
    const auto result = ma::get_unpaired_value(e.first);
    assert(result == e.second);
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

template<typename Size>
std::string
generate_input(const Size& size, ma::random_generator<int>& random_generator) {
  std::string large_str;
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "starting generation";
  auto before = std::chrono::system_clock::now();
  for (Size i = 0; i < size; ++i) {
    large_str.push_back(static_cast<char>(random_generator.generate() + '0'));
    if (i % 1000 == 0)
      std::cout << "." << std::flush;
  }
  auto after = std::chrono::system_clock::now();
  std::cout << "generated OK" << std::endl
      << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(after-before).count() << " seconds." << std::endl
      << std::endl;
  return large_str;
}
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
  ma::random_generator<size_type> random_size_generator(2, 100);
  ma::random_generator<element_type> random_element_generator(0, 9);
  for (size_t i = 0; i < number_of_generations; ++i) {
    const auto size = random_size_generator.generate();
    const auto input = generate_input<size_type>(size, random_element_generator);
    std::cout << "-----------------------------" << std::endl
        << __func__ << std::endl
        << "size: " << size  << std::endl
        << "input vector: [";
    for (size_t j = 0; j < size; ++j) {
      std::cout << input [j] << ", ";
//      if (j == 0)
//        std::cout << input [j] << " ";
//      if (j == 0 and size > 1)
//        std::cout << "... ";
//      if (j == size - 1)
//        std::cout << input[j];
    }
    std::cout << "]" << std::endl;
    const auto result = ma::number_of_valid_chains(input);
    std::cout << "number_of_valid_chains's result: " << result.first << std::endl;

    const auto result_enhanced = ma::number_of_valid_chains_enh(input);
    std::cout << "number_of_valid_chains enhanced's result: " << result_enhanced.first << std::endl;
    assert(result.first == result_enhanced.first);
    std::cout << "Assert OK!" << std::endl
        << "-----------------------------" << std::endl;
  }
}
/**/
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



