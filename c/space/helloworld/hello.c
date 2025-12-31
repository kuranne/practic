#include "hello.h"

char *dyin() {
    size_t size = 2, length = 0;
    int c;
    char *buf, *tmp, *fnl;

    if (!(buf = (char*)calloc(size, sizeof(char)))) return NULL;

    while ((c = getchar()) != EOF && c != '\n') {
        if (size == length + 1) {
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

    return (!(fnl = realloc(buf, (length + 1) * sizeof(char))))? buf: fnl;
}

void hello(char name[]) {
    printf("Hello %s!\n", name);
}