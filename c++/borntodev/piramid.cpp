#include <iostream>

int main() {
    int i, j, n = 5, p;
    for (i = 0; i < n; i++) {
        p = 0;
        for (j = 0; j < n + i; j++) {
            if (j > n - i - 2) {
                printf("%c", (p % 2 == 0)? '$': ' ');
                p++;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}