#include <stdio.h>

int main() {
    FILE *txt = fopen("text.txt", "r");
    int c;
    while ((c = fgetc(txt)) != '\0' && c != EOF) {
        printf("%c", (c >= 'a' && c <= 'z')? c - 32: c);
    }
    printf("\n");
    
    return 0;
}