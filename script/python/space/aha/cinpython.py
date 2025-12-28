import tempfile as tf
import subprocess as sp

def main():
    code = """
#include <stdio.h>
#define SIZE 1024

int main() {
    char buf[SIZE];

    fgets(buf, SIZE, stdin);
    fclose(stdin);

    fputs(buf, stdout);
    fclose(stdout);

    return 0;
}
"""

    with tf.NamedTemporaryFile(suffix=".c", delete=False) as f:
        f.write(code.encode())
        fname = f.name

    exe = fname.replace(".c", "")
    sp.run(["/usr/bin/clang", fname, "-o", exe])
    sp.run([exe])

if __name__ == "__main__":
    main()