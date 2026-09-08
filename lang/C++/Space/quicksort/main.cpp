#include "quicksort.h"
#include <iostream>
#include <vector>

using namespace std;

void print_vec(vector<int> vec) {
  for (int v : vec)
    cout << v << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {2, 3, 1, 4, 8, 7, 6, 9, 0};
  print_vec(arr);
  quicksort(arr, 0, arr.size() - 1);
  print_vec(arr);
  return 0;
}
