#include <iostream>

int main() {
    int c, big = 0, small = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if ('A' <= c && c <= 'Z') big = 1;
        if ('a' <= c && c <= 'z') small = 1;
        if (big + small == 2) break;
    }
    
    std::cout << ((big && small)? "Mix": (big)? "All Capital Letter": "All Small Letter") << std::endl;

    return 0;
}