#include <iostream>

using namespace std;

int main() {
    int n, i, j;
    cin >> n;

    for (i = 0; i < n * 2 - 1; i++) {
        if (i < n) {
        for (j = 0; j < n + i; j++)
            cout << ((j > n - i - 2)? '*': ' ');
        } else {
            for (j = n * 2 - ((i + 2) % n); j != -1; j--) {
                cout << (())
            }
        }
        cout << endl;
    }

    return 0;
}