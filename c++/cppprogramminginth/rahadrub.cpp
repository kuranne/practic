#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(){
    int i;
    string line, tx; vector<string> jote;
    vector<int> count;

    getline(cin, line);
    istringstream iss(line);

    while(iss >> tx){
        jote.push_back(tx);
    }

    for(i=0; i<jote.size(); i++){
        cout << jote[i].length();
    }
    cout << endl;

    return 0;
}