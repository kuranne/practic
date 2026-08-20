#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int ugly_number_at(int n) {
  if (n <= 0)
    return 0;

  vector<int> ugly(n, 1);
  vector<int> primes = {2, 3, 5};
  vector<int> ptrs(primes.size(), 0);

  for (int i = 1; i < n; i++) {
    int next = INT_MAX;

    for (size_t j = 0; j < primes.size(); j++) {
      next = min(next, ugly[ptrs[j]] * primes[j]);
    }

    ugly[i] = next;

    for (size_t j = 0; j < primes.size(); j++) {
      if (ugly[ptrs[j]] * primes[j] == next) {
        ptrs[j]++;
      }
    }
  }

  return ugly[n - 1];
}

int main() {
  int n;
  if (cin >> n)
    cout << ugly_number_at(n) << endl;
  return 0;
}
