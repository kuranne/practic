#include <stdio.h>
int a[101][101],b[101][101];
int mai, maj;
int main(){
    scanf("%d%d", &mai, &maj);
    for(int i = 0; i < mai; i+=1){
        for(int j = 0; j < maj; j+=1){
            scanf("%d", &a[i][j]);
        }
    }

    for(int i = 0; i < mai; i+=1){
        for(int j = 0; j < maj; j+=1){
            scanf("%d", &b[i][j]);
        }
    }

    for(int i = 0; i < mai; i+=1){
        for(int j = 0; j < maj; j+=1){
            printf("%d ", a[i][j] + b[i][j]);
        }
        printf("\n");
    }
    return 0;
}