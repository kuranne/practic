#include <stdio.h>

int main(){
    char character[10001];
    int isUp = 0, isLow = 0;
    scanf("%s", &character);

    for(int i = 0; character[i]; i++){
        if(character[i] >= 'A' && character[i] <= 'Z'){isUp++;}
        else{isLow++;}
    }
    printf((isUp == 0)?"All Small Letter\n":(isLow == 0)?"All Capital Letter\n":"Mix\n");
    return 0;
}