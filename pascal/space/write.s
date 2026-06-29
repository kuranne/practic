; file name: write.s
; as -o write.o write.s
; ld -o write write.o -lSystem -syslibroot 'xcrun --show-sdk-path' -e _main -arch arm64

.section __DATA,__data
    msg:    .asciz "Hello Arm64\n" ; len = 13

.section __TEXT,__text
    .global _main
    .align  2

_main:
    mov     x0, #1
    
    adrp    x1, msg@PAGE
    add     x1, x1, msg@PAGEOFF
    mov     x2, #13

    mov     x16, #4
    svc     #0

    ; ---

    mov     x0, #0
    mov     x16, #1
    svc     #0