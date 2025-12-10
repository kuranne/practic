#include <iostream>
#include <string>

using namespace std;

int main(){
    int i, n;
    cin >> n;
    for(i=1; i<=n; i++){
        string space(n-i, ' '), dokjan(2*(i-1)+1, '*');
        cout << space << dokjan << endl;
    }
    return 0;
}