#include <stdio.h>
#include <stdlib.h>

int main(){
    int column, row, ldprs, useprprsn;
    scanf("%d%d%d%d", &column, &row, &ldprs, &useprprsn);
    int *squar = (int*)malloc(sizeof(column*row*4));
    
    for(int i=0;i<column;i++){
        for(int j=0;j<row;j++){
            scanf("%d", &squar);
        }
    }
    
    printf("%d", squar);

    free(squar);
    return 0;
}