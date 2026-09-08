#include <stdio.h>
#include <stdlib.h>

void hello(const char *name)
{
    printf("Hello, %s!", name);
}

char *recieve()
{
    size_t size = 2, length = 0;
    int c;
    char *ptr = (char *)calloc(size, sizeof(char));
    if (!ptr)
        return NULL;

    while ((c = getchar()) != '\0' && c != EOF)
    {
        if (size == length + 1)
        {
            size *= 2;
            char *tmp = (char *)realloc(ptr, size);

            if (!tmp)
            {
                free(ptr);
                return NULL;
            }

            ptr = tmp;
        }
        ptr[length++] = c;
    }
    char *fnl = (char *)realloc(ptr, length + 1);
    if (!fnl)
    {
        free(ptr);
        return NULL;
    }
    fnl[length] = '\0';
    return fnl;
}

void free_c_char(char *ptr)
{
    free(ptr);
}