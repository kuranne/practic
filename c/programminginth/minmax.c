#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int nnumbers[n];

    for(int i = 0; i < n; i+=1){
        scanf("%d", &nnumbers[i]);
    }
    int max = nnumbers[0];
    int min = nnumbers[0];
    
    for(int i = 0; i < n; i+=1){
        if(max < nnumbers[i]){
            max = nnumbers[i];
        }
        if(min > nnumbers[i]){
            min = nnumbers[i];
        }
    }
    printf("%d\n%d\n", min, max);
    return 0;
}