#include <stdio.h>

int main(){
    int a,b,c;
    scanf("%d%d%d", &a, &b, &c);
    int d = a+b+c;
    char* grade;
    if(d >= 80){
        grade = "A";
    }
    else if(d >=75){
        grade = "B+";
    }
    else if(d >=70){
        grade = "B";
    }
    else if(d >= 65){
        grade = "C+";
    }
    else if(d >= 60){
        grade = "C";
    }
    else if(d >= 55){
        grade = "D+";
    }
    else if(d >= 50){
        grade = "D";
    }
    else{
        grade = "F";
    }
    printf("%s\n", grade);
    return 0;
}