#include <iostream>

using namespace std;

int main() {
    int a, b;
    string ans;
    cin >> a >> b;
    if (a > b) ans = "A"; else
    if (a < b) ans = "B";
    else ans = "AB";

    cout << ans << endl;
    return 0;
}