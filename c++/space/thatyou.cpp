// argtest
// argtest.cpp
//Create by Wirakorn Thanabat

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    int i, j;
    string text;
    if(argc > 1){
        for(i=1; i<argc; i++){
            text = argv[i];
            size_t pos = text.find("Maisa");
            if(pos != string::npos){
                cout << "That you! " << text.substr(pos, 5) << "!" << endl;
            } else {cout << "Who are u?" << endl;}
        }
    }
    return 0;
}