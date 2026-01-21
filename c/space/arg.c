#include <stdio.h>

int main(int argv, char *argc[]) {
    if (argv > 1) printf("hello, %s !", argc[1]);
    else printf("Hello World!");
    return 0;
}