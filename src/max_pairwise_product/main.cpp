/*
 * main.cpp
 *
 *  Created on: Dec 24, 2016
 *      Author: marcos
 */

#include <iostream>
#include <vector>

#include "max_pairwise_product.h"

using std::cin;
using std::cout;
using std::vector;

namespace ma = mjlopez::algorithms;

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    std::pair<int,int> result_pair = ma::max_pairwise_product(numbers);
    cout << "result: " << result_pair.first << "\n";
    cout << "operations: " << result_pair.second << "\n";
    return 0;
}



