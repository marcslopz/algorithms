/*
 * light_chains.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: marcos
 */


#include <iostream>

#include "odd_occurrences.h"
#include "sort/merge_sort.h"

namespace ma = mjlopez::algorithms;

using std::cout;
using std::endl;
using std::vector;

int ma::get_unpaired_value(const vector<int>& input) {
  const auto sorted = ma::merge_sort(input, 0, input.size());
  cout << "input: [";
  for (const auto e: input)
    cout << e << ", ";
  cout << "]" << endl;
  const vector<int>& sorted_vector = sorted.first;
  cout << "sorted_input: [";
  for (const auto e: sorted_vector)
    cout << e << ", ";
  cout << "]" << endl;
  int previous_element = 0;
  for (const auto& el: sorted_vector) {
    cout << "el:" << el << ", previous_element: " << previous_element << endl;
    if (previous_element == 0) {
      previous_element = el;  /// don't compare, is the first of the pairs
      cout << "#0: not compared" << endl;
    } else {
      if (el == previous_element) {
        cout << "#1: is a match" << endl;
        previous_element = 0; /// paired OK, the next element won't have to be compared
      } else {
        cout << "#2: is different, return it!" << endl;
        return previous_element;  /// we've found the unpaired element
      }
    }
  }
  cout << "#3: weird case" << endl;
  return previous_element; /// it means there is no unpaired element in the input vector
}
