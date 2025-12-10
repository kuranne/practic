#include <iostream>
#include <string>
#include <map>
#define unSyu ios_base::sync_with_stdio(false); std::cin.tie(NULL);
using namespace std;

signed main() {
    map<string, int> age;
    age["Maisa"] = 18;
    age.insert({"Miewsa", 17});
    age.insert({"Maosa", 16});
    for (auto &val: age) cout << val.first << " is " << val.second << endl;
    return 0;
}w