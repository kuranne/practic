#include <stdio.h>

void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);

int main() {
    int arr[] = {0, 2, 4, 8, 9, 7, 5, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    quicksort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

__attribute__((weak))
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

__attribute__((weak))
int partition(int arr[], int low, int high){ // |x|y|
    int right = arr[high]; // right number
    int left = low - 1; // index left

    for (int j = low; j < high; j++) { // run from left to right
        if (arr[j] < right) { // if found that num -lt the right
            swap(&arr[++left], &arr[j]); // swap it with the number at the next of sorted number
        }
    }

    swap(&arr[++left], &arr[high]);
    return left; // return index of leftover |////|XXXX|
}

__attribute__((weak))
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high); // middle

        quicksort(arr, low, pivot - 1); // sort left
        quicksort(arr, pivot + 1, high); // sort right
    }
}
