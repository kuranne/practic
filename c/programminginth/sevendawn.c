#include <stdio.h>
#include <stdlib.h>

int main(){
    int *dawn = (int*)calloc(9, sizeof(int)), i, j, sum = 0;
    
    for (i = 0; i < 9; i++){
        scanf("%d", &dawn[i]); sum += dawn[i];
    }

    int imposter = sum - 100;

    for (i = 1; i < 9; i++){
        for (j = 0; j < i; j++){
            if (i==j){continue;}
            if ((dawn[i]+dawn[j]) == imposter) {
                dawn[i] = 0;
                dawn[j] = 0;
                break;
            }
        }
    }

    for (i = 0; i < 9; i++){if (dawn[i] != 0) {printf("%d\n", dawn[i]);}}
    return 0;
}