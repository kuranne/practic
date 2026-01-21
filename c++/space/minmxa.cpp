#include <iostream>
#include <cmath>

int main(){
    int lenge, maxi=(-2)*pow(10,9), minni=2*pow(10,9), todefine; 
    std::cin >> lenge;
    for (int i=0;i<lenge;i++) {
        std::cin >> todefine;
        if (todefine>maxi){
            maxi = todefine;
        }
        if (todefine<minni){
            minni = todefine;
        }
    }

    std::cout << minni << '\n' << maxi << std::endl;
    return 0;
}