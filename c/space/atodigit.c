#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum {
    OFF, ON
} Status;

int convertToDigit(char byte[], int type) {
    int num = 0, length = strlen(byte), c;
    
    for (int i = 0; i < (int)strlen(byte); i++) {
        int tmp = ((c = byte[--length]) >= '0' && c <= '9') ? c - '0': c - 'A' + 10;
        num += tmp * (int)pow((double)type, (double)i);
    }
    
    return num;
}

char *cdyin() {
    size_t size = 2, length = 0;
    int c;
    char *buf, *tmp, *fnl;
    if (!(buf = (char*)calloc(size, sizeof(char)))) return NULL;
    while ((c = getchar()) != '\0' && c != EOF && c != '\n') {
        if ( length + 1 == size) {
            size *= 2;
            if (!(tmp = realloc(buf, size * sizeof(char)))) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[length++] = c;
    }
    buf[length] = '\0';
    return (!(fnl = realloc(buf, sizeof(char) * (length + 1))))?buf:fnl;
}

int main() {
    Status stt;
    char number, type;
    
    scanf("%d", &stt); // input for service type
    scanf("%s %s", &number, type); // input >> number & type
    
    if (stt == OFF) {
        printf("digit is: %d\n", convertToDigit(number, atoi(type)));
    }
    //else {
        // printf("base %d is: %d\n", atoi(type), );
    // }

    return 0;
}