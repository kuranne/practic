#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]){
    int i;
    if(argc>1){
        for(i=1; i<argc; i++){
            printf("Hello %s!\n", argv[i]);
        }
    }else
    {
        printf("Hello World!\n");
    }
    return 0;
}