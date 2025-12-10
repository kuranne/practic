#include <iostream>

using namespace std;

int main(){
    int i, j, m, n, l, k, c, expense = 0, temp;
    cin >> n >> m >> l >> k >> c;

    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            cin >> temp;
            expense += temp;
        }
    }

    expense += k * l * c;
    expense = (expense%c==0)?(expense/c):((expense/c)+1);
    cout << expense << endl;
    return 0;
}