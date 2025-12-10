import tempfile, subprocess

code = """
#include <stdio.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\\n", a + b);
    return 0;
}
"""

with tempfile.NamedTemporaryFile(suffix=".c", delete=False) as f:
    f.write(code.encode())
    fname = f.name

fexe = fname.replace(".c", "")
subprocess.run(["gcc", fname, "-o", fexe])
subprocess.run([fexe])