#include <stdio.h>
#ifdef __x86_64__
    #define ARCH "x86_64"
#else
    #define ARCH "aarch64"
#endif

int main(int argc, char argv[]) {
    if (argc > 1) {
        fprintf(stdout, "Hello %s!, in %s\n", argv[1], ARCH);
    }
    else {
        fprintf(stdout, "Hello World! in %s\n", ARCH);
    }
}

#undef ARCH