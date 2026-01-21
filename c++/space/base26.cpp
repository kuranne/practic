#include <iostream>
#include <string>

using namespace std;

class Converter {
    private:
        int conv = 1;
    public:
        int convert(string number) {
            int 
            len = number.length(),
            current = 0;

            for (auto c: number) {
                current += ( c - ((c >= 'A' && c <= 'Z')?'A' - 1:'a' - 1) ) * conv;
                conv *= 26;
            }

            return current;
        }

};

signed main() {
    Converter solve;
    string number;
    cin >> number;

    cout << solve.convert(number) << endl;
    
    return 0;
}