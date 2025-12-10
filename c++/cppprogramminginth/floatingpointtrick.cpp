#include <bits/stdc++.h>

using namespace std;

int main(){
    size_t n; int i;
    cin >> n;
    
    for (i = 0; i < n; i++){
        long double ques;
        cin >> ques;
        cout << fixed << setprecision(0) << pow(2, ques) << endl;
    }

    return 0;
}