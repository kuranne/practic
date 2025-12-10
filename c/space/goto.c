#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n == 10) {
        goto n_is_receive;
    }
    printf("N is not ten\n");

n_is_receive:
    printf("N is Receive\n");

    return 0;
}