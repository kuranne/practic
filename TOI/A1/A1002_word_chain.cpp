#include <iostream>

using namespace std;

signed main() {
    int len, line, bk = 0;
    string prev, cur;

    cin >> len >> line;

    for (int i = 0; i < line; i++) {
        cin >> cur;
        int score = 0;

        if (!i) goto skip;

        for (int j = 0; j < len; j++) {
            if (cur[j] != prev[j]) score++;
            if (score > 2) {
                bk = 1;
                goto output;
            }

        }

        skip:
            prev = cur;
    }
    output:
        cout << (bk ? prev : cur) << endl;
    return 0;
}