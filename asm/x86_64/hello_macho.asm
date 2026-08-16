global _main

section .text
_main:
    mov rax, 0x2000004
    mov rdi, 1
    lea rsi, [rel msg]
    mov rdx, 14
    syscall

    mov rax, 0x2000001
    xor rdi, rdi
    syscall

section .data
    msg db "Hello, MachO!", 10