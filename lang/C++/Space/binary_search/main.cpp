#include "../quicksort/quicksort.h"
#include "binary_search.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int main() {
  std::vector<int> arr(1000);
  std::iota(arr.begin(), arr.end(), 964);
  std::shuffle(arr.begin(), arr.end(), std::mt19937());

  quicksort(arr, 0, arr.size() - 1);
  std::cout << binary_search(arr, 1738) << std::endl;
  return 0;
}
