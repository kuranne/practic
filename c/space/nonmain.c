#include <stdio.h>
#include <stdlib.h>

int mymain();

void _start() {
    int ret = mymain();
    exit(mymain());
}

int mymain() {
    printf("Hello World!");
    return 0;
}