.global main
.text

.section .rodata
printf_fmt:
    .string "%ld\n"
scanf_fmt:
    .string "%ld %ld"

.text
main:
    push %rbp
    mov %rsp, %rbp
    subq $16, %rsp

    lea scanf_fmt(%rip), %rdi
    lea -8(%rbp), %rsi
    lea -16(%rbp), %rdx
    movl $0, %eax
    call scanf@PLT

    mov -8(%rbp), %rdi
    mov -16(%rbp), %rsi
    call aplusb

    lea printf_fmt(%rip), %rdi
    mov %rax, %rsi
    movl $0, %eax
    call printf@PLT

    movq $0, %rax
    leave
    ret
