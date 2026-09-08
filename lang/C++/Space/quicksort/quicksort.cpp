#include "quicksort.h"

int partition(std::vector<int> &arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++)
    if (pivot > arr[j])
      std::swap(arr[++i], arr[j]);

  std::swap(arr[++i], arr[high]);

  return i;
}

void quicksort(std::vector<int> &arr, int low, int high) {
  if (low < high) {
    int pvidx = partition(arr, low, high);
    quicksort(arr, low, pvidx - 1);
    quicksort(arr, pvidx + 1, high);
  }
}
