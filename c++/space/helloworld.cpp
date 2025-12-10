extern "C" void _start() {
    const char msg[] = "Hello, world\n";
    asm volatile(
        "mov $0x2000004, %%rax\n\t"  // syscall: write (macOS)
        "mov $1, %%rdi\n\t"           // fd: stdout
        "lea %0, %%rsi\n\t"           // buf
        "mov $13, %%rdx\n\t"          // len
        "syscall\n\t"
        "mov $0x2000001, %%rax\n\t"   // syscall: exit
        "xor %%rdi, %%rdi\n\t"
        "syscall\n\t"
        :
        : "m"(msg)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
}