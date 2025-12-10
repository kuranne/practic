#include <iostream>
#include <string>

using namespace std;

int main() {
    string name; int c;
    while ((c = getchar()) != '\n') name += c;
    cout << "Hello " << name << " !" << endl << "Sommai 108 Eleven Shop" << endl;
    return 0;
}