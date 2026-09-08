#include "binary_search.h"

int binary_search(std::vector<int> &arr, int target) {
  int left = 0, right = arr.size() - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (arr[mid] == target)
      return mid;
    if (arr[mid] < target)
      left = mid + 1;
    if (arr[mid] > target)
      right = mid - 1;
  }

  return -1;
}
