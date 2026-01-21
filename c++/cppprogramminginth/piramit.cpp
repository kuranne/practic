#include <iostream>
#include <string>

using namespace std;

int main(){
    int i, n;
    cin >> n;

    for(i=1; i<=n; i++){
        string dokjan(i, '*');
        cout << dokjan << endl;
    }

    return 0;
}