#include "function.h"

int main() {
    FILE *data = fopen("data.txt", "r");
    size_t size = 2, length = 0;
    int check, c, *arr, *tmp;
    
    if (!(tmp = (int*)calloc(size, sizeof(int)))) return 1;

    while ((check = fscanf(data , "%d", &c))) {
        if (size == length + 1) {
            size *= 2;
            if (!(arr = realloc(tmp, size * sizeof(int)))) {
                free(tmp);
                goto error;
            }
            tmp = arr;
        }
        tmp[length++] = c;
    }
    if (!(arr = realloc(tmp, (--length) * sizeof(int)))) {
        free(tmp);
        goto error;
    }

    quicksort(arr, 0, (int)length - 1);
    int target;
    scanf("%d", &target);
    printf("%d\n", binarysearch(arr, length, target));

    
success:
    fclose(data);
    return 0;
    
error:
    fclose(data);
    return 1;
}