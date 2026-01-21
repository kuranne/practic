#include <iostream>

using namespace std;

int main(){
    int line, length, i, errline;
    cin >> length >> line >> errline;
    while(line--) {
        for(i = 0; i<length; i++) {
            if(line == errline) {
                cout << "B";
            }else {
                cout << (char)(i%26 + 'A');
            }
        }
        cout << endl;
    }

    return 0;
}