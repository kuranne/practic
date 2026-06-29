; file name: calc.s
; as -o calc.o calc.s
; ld -o calc calc.o -lSystem -syslibroot `xcrun --show-sdk-path` -e _main -arch arm64

.section __DATA,__data
    a:      .quad 1
    b:      .quad 2
    sum:    .quad 0
    fmt:    .asciz "result is: %lld\n"

.section __TEXT,__text
    .global _main
    .align 2

_main:
    ; --- sum := a + b ---
    adrp    x0, a@PAGE
    ldr     x0, [x0, a@PAGEOFF]

    adrp    x1, b@PAGE
    ldr     x1, [x1, b@PAGEOFF]

    add     x2, x1, x0

    adrp    x3, sum@PAGE
    str     x2, [x3, sum@PAGEOFF]

    ; --- printf ---
    stp     fp, lr, [sp, #-16]!
    
    adrp    x0, fmt@PAGE
    add     x0, x0, fmt@PAGEOFF

    mov     x1, x2
    bl      _printf

    ; --- end ---
    ldp     fp, lr, [sp], #16
    mov     x0, #0
    ret
