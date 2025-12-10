#include <iostream>
#include <cmath>

using namespace std;

signed main() {
    int n;
    cin >> n;

    for (int i = 3; i < sqrt(n); i+=2) {
        if (n % i == 0){
            cout << "isn't Prime" << endl;
            return 0;
        }
    }

    cout << "is Prime!" << endl;
    return 0;
}