#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int arr[1000];

    for (int i = 0; i < 1000; i++)
        arr[i] = i + 1;

    srand(time(NULL));

    for (int i = 999; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    for (int i = 0; i < 1000; i++) {
        printf("%d%c", arr[i], (i % 20 == 19) ? '\n' : ',');
    }

    return 0;
}