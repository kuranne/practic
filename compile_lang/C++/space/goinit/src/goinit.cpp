//
// goinit
// goinit.cpp
// 
// Create by Wirakorn Thanabat

#include <iostream>
#include <cstdlib>
#include <string>

int goinit(std::string name){
    std::string command = "mkdir " + name + " && cd " + name + " && go mod init "+ name + " && touch main.go";
    return system(command.c_str());
}

int main(int argc, char* argv[]){
    std::string name;
    int i;
    if(argc > 0){
        for(i=1; i<argc; i++){
            name += argv[i];
        }
        if(goinit(name)){
            return 1;
        }
    }
    return 0;
}