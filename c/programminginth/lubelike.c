#include <stdio.h>
#include <stdlib.h>

int compar(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}

int main(){
    int n, i, j, forc=0, hescore=0;
    scanf("%d", &n);

    int *post = (int*)calloc(n, sizeof(int));
    int *postarry = (int*)calloc(n, sizeof(int));

    for(i=0; i<n; i++){

        int ptemp;
        scanf("%d", &ptemp);

        for(j=0; j<=i; j++){
           if(ptemp!=post[j]&&post[j]==0){
                post[j] = ptemp;
                postarry[j] = 1;
                forc ++;
                break;
            } else if(ptemp == post[j]){
                postarry[j]++;
                break;
            }
        }
    }    

    int *winn = (int*)calloc(forc, sizeof(int)), winc=0;

    for(i=0; i<n; i++){
        if(post[i] == 0){
            break;
        }
        
        if(hescore<postarry[i]){
            hescore = postarry[i];
            continue;
        }
    }

    for(i=0; i<n; i++){
        if(post[i] == 0){
            break;
        }

        if(postarry[i] == hescore){
            winn[winc++] = post[i];
        }
    }

    qsort(winn, winc, sizeof(int), compar);

    for(i=0; i<winc; i++){
        printf("%d ", winn[i]);
    }
    printf("\n");

    free(post);
    free(postarry);
    free(winn);
    return 0;
}