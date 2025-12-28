#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define endl printf("\n")

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int arr[], int low, int high) {
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < arr[high]) {
            swap(&arr[j], &arr[++i]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);

        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}

char *cin() {
    size_t size = 2, length = 0;
    char *buf, *fnl, *tmp;
    int c;

    FILE *fin = fopen("data.txt", "r");

    if (!(buf = (char*)calloc(size, sizeof(char)))) return NULL;

    while ((c = getc(fin)) != EOF) {
        if (length + 1 == size) {
            size *= 2;
            if (!(tmp = realloc(buf, sizeof(char) * size))) {fclose(fin); free(buf); return NULL;}
            buf = tmp;
        }
        buf[length++] = c;
        
        if (c == '\n') break;
    }

    fclose(fin);
    buf[length] = '\0';


    return (!(fnl = realloc(buf, length + 1)))? buf: fnl;
}

int main() {
    char *buf = cin();
    if (strlen(buf) <= 0) {free(buf); return 0;}
    int *arr = (int*)calloc(strlen(buf), sizeof(int)), length = 0, *tmp;

    for (int i = (int)(strlen(buf) - 1); i >= 0; i--) {
        if (buf[i] == '\n' || buf[i] == '\0') continue;
        int tmp = 0, d = 1;
        
        while (buf[i] != ' ' && i >= 0) {
            tmp += (int)(buf[i--] - '0') * d;
            d *= 10;
        }

        arr[length++] = tmp;
    }

    if (!(tmp = (int*)realloc(arr, sizeof(int) * (length + 1)))) {
        goto error;
    }

    arr = tmp;

    quicksort(arr, 0, length - 1);

    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }

    endl;

    free(buf);
    free(arr);
    return 0;

error:
    free(buf);
    free(arr);
    return 1;
}