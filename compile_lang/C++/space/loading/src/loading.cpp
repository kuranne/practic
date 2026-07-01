#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    int total = 20;
    cout << "loading....." << endl;
    for (int i = 0; i <= total; i++) {
        cout << "\r[";
        for (int j = 0; j < i; j++) {
            cout << "=";
        }
        for (int j = 0; j < total - i; j++) {
            cout << " ";
        }
        cout << "]" << (i * 5) << "%" << flush;
        usleep(120000);
    }
    cout << "\n\ncomplete!\n";
    return 0;
}