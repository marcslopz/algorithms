#include <cstdlib>

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


void
test_large_case() {}
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
