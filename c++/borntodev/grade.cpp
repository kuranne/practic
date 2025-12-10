#include <iostream>

using namespace std;

int main() {
    int n, g;
    cin >> n;
    if (n >= 80) g = 0; else
    if (n >= 70) g = 1; else
    if (n >= 60) g = 2; else
    if (n >= 50) g = 3;
    else g = 5;

    printf("%c", g + 'A');

    return 0;
}