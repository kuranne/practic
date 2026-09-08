#include "Solution.h"
#include <iostream>

using namespace std;

int main() {
  int n;
  if (cin >> n) {
    Solution sol;
    cout << ((sol.isUgly(n)) ? "true" : "false") << endl;
  }
  return 0;
}
