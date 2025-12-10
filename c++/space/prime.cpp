#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool cprime(vector<uint64_t> &arry, uint64_t &cadidate) {
    uint64_t lmt = sqrt(cadidate) + 1;
    for (uint64_t i:arry) {
        if (i > lmt) return true;
        if (cadidate % i == 0) return false;
    }
    return true;
}

signed main() {
    vector<uint64_t> prime = {2};
    uint64_t cadidate = 3, n, length = 1;
    
    cin >> n;
    fclose(stdin);

    while (length < n) {
        if (cprime(prime, cadidate)) {
            prime.push_back(cadidate);
            length++;
        }
        cadidate += 2;
    }

    cout << prime[length - 1] << endl;
    fclose(stdout);

    return 0;
}