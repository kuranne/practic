import subprocess as spc
import tempfile as tf

code = """
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    printf("The number is %d\\n", n);
    return 0;
}
"""

with tf.NamedTemporaryFile(suffix=".c", delete=False) as f:
    f.write(code.encode())
    fname = f.name

exe = fname.replace(".c", "")
spc.run(["gcc", fname, "-o", exe])
spc.run([exe])