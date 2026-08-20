#include "Solution.h"

bool Solution::isUgly(int n) {
  if (n <= 0) {
    return false;
  } else if (n == 1 || n == 2 || n == 3 || n == 5) {
    return true;
  }

  std::vector<int> prime_nums = Solution::primes(n);
  std::vector<int> uglynum = {2, 3, 5};

  int max = uglynum[0];
  for (int i = 1; i < uglynum.size(); i++)
    if (max < uglynum[i])
      max = uglynum[i];

  for (int p : prime_nums) {
    if (n % p == 0 && p > max)
      return false;
  }

  return true;
}

std::vector<int> Solution::primes(int n) {
  std::vector<int> prime = {2, 3};

  for (int cadidate = 5; cadidate <= n; cadidate += 2) {
    bool is_prime = true;

    for (int p : prime) {
      if (cadidate % p == 0) {
        is_prime = false;
        break;
      }
    }

    if (is_prime)
      prime.push_back(cadidate);
  }

  return prime;
}
