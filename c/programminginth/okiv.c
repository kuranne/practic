#include <stdio.h>
#include <string.h>
int main(){
    char quest[16];
    scanf("%s",&quest);
    int ope = strlen(quest);
    for(int i=1;i<6;i++){
        int count =0;
        printf((i%3==0)?"\n#":(i==1)?".":"\n.");
        for(int j=1;j<=(ope*2);j++){
            if(i==1||i==5){ /*first line and last line*/
                if(j%2==1){
                    printf(((j+1)%3==0)?".*.":".#.");
                }else{
                    printf(".");
                }
            }
            
            if(i==2||i==4){ /*second line and fouth line*/
                if(j%2==1){
                    printf(((j+1)%6==0)?"*.*":"#.#");
                }else{
                    printf(".");
                }
            }
            
            if(i==3){ /*center*/
                if(count!=3){
                    count++;
                    printf((j%2==1)?".%c.":"#",quest[((j+1)/2)-1]);
                }else if(j == ope*2){
                    printf("#");
                    break;
                }else{
                    count=0;
                    printf("*.%c.*",quest[((j+2)/2)-1]);
                    j+=2;
                }
            }
        }
    }
    printf("\n");return 0;
}