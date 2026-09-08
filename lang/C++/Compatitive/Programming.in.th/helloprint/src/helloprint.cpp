#include <iostream>

void HelloWorld(auto s){
    std::cout << ((s == "printf")?"HelloWorld":s) << std::endl;
}

int main(){
    HelloWorld("printf");
    return 0;
}