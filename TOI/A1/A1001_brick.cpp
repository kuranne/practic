#include <iostream>
#include <string>
#include <vector>

using namespace std;

signed main() {
    int mn[2];
    cin >> mn[0] >> mn[1];

    vector<string> mapping;

    for (int i = 0; i < mn[0]; i++) {
        string tmp;
        cin >> tmp;
        mapping.push_back(tmp);
    }
    
    for (int i = 0; i < mn[1]; i++) {
        int brick, idx = mn[0] - 1;
        cin >> brick;

        for (int j = 0; j < mn[0]; j++) {
            if (mapping[j][i] == 'O') {
                idx = j - 1;
                break;
            }
        }

        while (brick > 0 && idx >= 0) {
            mapping[idx--][i] = '#';
            brick--;
        }
    }

    for (string line: mapping) cout << line << endl;

    return 0;
}