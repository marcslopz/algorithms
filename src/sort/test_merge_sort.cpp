#include <cstdlib>
#include <chrono>
#include <iostream>

#include "merge_sort.h"
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
  const auto result_empty_vector = ma::merge_sort(empty_vector, 0, 0);
  assert(result_empty_vector.first.size() == empty_vector.size());

  /// one-component vector
  const int component_one = 1;
  const int component_five = 5;
  std::vector<int> one_component_vector = {component_one};
  auto result_one_component_vector = ma::merge_sort(one_component_vector, 0, 1);
  assert(result_one_component_vector.first.size() == one_component_vector.size());
  one_component_vector = {component_five};
  result_one_component_vector = ma::merge_sort(one_component_vector, 0, 1);
  assert(result_one_component_vector.first.size() == one_component_vector.size());

  /// two-component vector already sorted
  std::vector<int> two_component_vector = {component_one, component_five};
  auto result_two_component_vector = ma::merge_sort(two_component_vector, 0, two_component_vector.size());
  assert(result_two_component_vector.first.size() == two_component_vector.size());
  assert(result_two_component_vector.first.front() == component_one);
  assert(result_two_component_vector.first.back() == component_five);

  /// two-component vector unsorted
  two_component_vector = {component_five, component_one};
  result_two_component_vector = ma::merge_sort(two_component_vector, 0, two_component_vector.size());
  assert(result_two_component_vector.first.size() == two_component_vector.size());
  assert(result_two_component_vector.first.front() == component_one);
  assert(result_two_component_vector.first.back() == component_five);
}

void
test_easy_case() {
  /// n-component vector
  const std::vector<int> easy_vector = {1, 7, 5, 15, 7, 10};
  const std::vector<int> expected_sorted_vector = {1, 5, 7, 7, 10, 15};
  const auto result_easy_vector = ma::merge_sort(easy_vector, 0, easy_vector.size());
  assert(result_easy_vector.first.size() == expected_sorted_vector.size());
  for (size_t i = 0; i < expected_sorted_vector.size(); ++i)
    assert(result_easy_vector.first[i] == expected_sorted_vector[i]);
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
  const auto result_large_vector = ma::merge_sort<uint32_t,uint64_t>(large_vector, 0, large_vector.size());
  after = std::chrono::system_clock::now();
  std::cout << "generated OK" << std::endl
//      << "Result: " << result_large_vector.first << std::endl
      << "Operations: " << result_large_vector.second << std::endl
      << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(after-before).count() << " seconds." << std::endl
      << std::endl;
  return result_large_vector.second;
}
void
test_large_case() {
  std::pair<size_t,size_t> input_sizes(1e4,1e5);
  std::pair<size_t,uint64_t> number_of_ops;

  number_of_ops.first = test_large_case(input_sizes.first);
  number_of_ops.second = test_large_case(input_sizes.second);
  ma::order actual_order = ma::calculate_order(input_sizes, number_of_ops);
  std::cout << "---------------------------" << std::endl
      << __func__ << std::endl
      << "first input size: " << input_sizes.first << std::endl
      << "second input size: " << input_sizes.second << std::endl
      << "first number of ops: " << number_of_ops.first << std::endl
      << "second number of ops: " << number_of_ops.second << std::endl
      << "order of algorithm: " << ma::as_string(actual_order) << std::endl;
  assert(actual_order == ma::order::nlogn);
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
