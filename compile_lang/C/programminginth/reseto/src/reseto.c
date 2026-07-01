#include <stdio.h>
#include <stdlib.h>

int find_first(int exclude[], int n) {
    for (int j = 2; j <= n; j++) {
        for (int i = 0; i < n; i++) {
            if (exclude[i]) {
                if (j == exclude[i]) {
                    break;
                }
            } else {return j;}
        }
    }

    return -1;
}

int contain(int arr[], int size, int n) {
    for (int i = 0; i < size; i++) {
        if (!arr[i]) {return 0;}
        if (arr[i] == n) {
            return 1;
        }
    }
    return 0;
}

signed main() {
    var:
        int n, k, ki = 0, *used; scanf("%d %d", &n, &k);

    start:
        if (!(used = (int*)calloc(n, sizeof(int)))) return 1;

        while (ki < k) {
            int fi = find_first(used, n);
            if (fi < 0) {goto clear;}
            used[ki++] = fi;

            for (int i = fi; i <= n && ki < k; i += fi) {
                if (contain(used, n, i)) {continue;}
                else used[ki++] = i;
            }
        }

    result:
        printf("%d\n", used[ki - 1]);        

    clear:
        free(used);
        return 0;
}