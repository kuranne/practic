#include <iostream>
#include <vector>
#define MATRIXADDITIONAL cin.tie(NULL); ios_base::sync_with_stdio(false);

using namespace std;

typedef vector<vector<int>> Matrix;

signed main() {
    MATRIXADDITIONAL

    Matrix matrix;
    int m, n, row, col, tmp;
    cin >> m >> n;

    for (row = 0; row < m; row++) {
        matrix.resize(row + 1);
        for (col = 0; col < n; col++) {
            cin >> tmp;
            matrix[row].push_back(tmp);
        }
    }

    for (auto &row: matrix) {
        for (int &col: row) {
            cin >> tmp;
            col += tmp;
        }
    }

    for (auto row: matrix) {
        for (int col: row) {
            cout << col << " ";
        }
        cout << endl;
    }

    return 0;
}