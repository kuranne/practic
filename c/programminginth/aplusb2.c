#include <stdio.h>
#include <stdlib.h>

char* input() {
    size_t size = 2, len = 0;
    int c;
    char *buf, *tmp, *fnl;

    if (!(buf = (char*)calloc(size, sizeof(char)))) return NULL;

    while ((c = getchar()) != '\n' && c != '\0' && c != EOF && c != ' ') {
        if (size == len - 1) {
            size *= 2;
            if (!(tmp = (char*)realloc(buf, size * sizeof(char)))) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[len++] = c;
    }
    buf[len] = '\0';

    return (fnl = (char*)realloc(buf, (len + 1) * sizeof(char))) ? fnl : buf;
}

int lenof(char* str) {
    int i = 0;
    
    while (str[i] !='\0' && str[i] != EOF) i++;
    return i;
}

void out(char* str) {
    int len = lenof(str), i;
    for (i = 0; i < len; i++)
        putc(str[i], stdout);
}
void outln(char* str) {
    out(str);
    putc('\n', stdout);
}

int parse_int(char* str) {
    int ret = 0, c, len = lenof(str), i;
    while ((c = str[i]) <= ' ') i++;
    int neg = (c == '-');
    if (neg) i++;
    for (i; (c = str[i]) >= '0' && c <= '9'; i++) {
        ret = ret * 10 + (c - '0');
    }
    return (neg) ? -ret : ret;
}

signed main() {
    char* test = input();
    outln(test);

    fclose(stdout);
    free(test);
    return 0;
}
