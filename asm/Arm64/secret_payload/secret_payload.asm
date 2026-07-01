// Author: Kuranne Maisa
// Design for macOS arm64
// File name: secret_payload.asm

.global _main
.align 2

.text
_main:
    ; Load the base address of the encrypted message into x0
    adrp x0, msg@PAGE[cite: 3]
    add x0, x0, msg@PAGEOFF[cite: 3]

    // -------------------------------------------------------
    // Stage 1: Decrypt "Welcome to CSTU41\n" (18 bytes) with key 0xAA
    // -------------------------------------------------------
    mov x1, #0              ; i = 0 (Loop counter / byte offset)[cite: 3]
    mov x2, #0xAA           ; Load single-byte XOR key[cite: 3]

_stage1_loop:
    ldrb w3, [x0, x1]       ; Load encrypted byte: w3 = msg[i][cite: 3]
    eor w3, w3, w2          ; Decrypt: w3 ^= 0xAA[cite: 3]
    strb w3, [x0, x1]       ; Store decrypted byte back into memory[cite: 3]
    add x1, x1, #1          ; Increment index (i++)[cite: 3]
    cmp x1, #18             ; Check if 18 bytes have been processed[cite: 3]
    b.ne _stage1_loop       ; If i != 18, loop again[cite: 3]

    // -------------------------------------------------------
    // Stage 2: Decrypt "art_krn.ms" (10 bytes) using "Welcome to" prefix as key
    // -------------------------------------------------------
    mov x1, #0              ; Reset loop counter for stage 2 (i = 0)[cite: 3]

_stage2_loop:
    ldrb w2, [x0, x1]       ; Load decrypted prefix byte to use as key: w2 = msg[i][cite: 3]
    add x3, x1, #18         ; Calculate target offset: x3 = i + 18[cite: 3]
    ldrb w4, [x0, x3]       ; Load encrypted trailing byte: w4 = msg[i + 18][cite: 3]
    eor w4, w4, w2          ; Decrypt: msg[i + 18] ^= msg[i][cite: 3]
    strb w4, [x0, x3]       ; Store decrypted flag byte back into memory[cite: 3]
    add x1, x1, #1          ; Increment index (i++)[cite: 3]
    cmp x1, #10             ; Check if 10 bytes have been processed[cite: 3]
    b.ne _stage2_loop       ; If i != 10, loop again[cite: 3]

    // -------------------------------------------------------
    // macOS Write System Call (sys_write)
    // NOTE: Intentionally printing only 18 bytes to hide the decrypted flag.
    // Reversers must use lldb (e.g., `memory read`) at this breakpoint to dump the rest.
    // -------------------------------------------------------
    mov x0, #1              ; Arg 0: File descriptor (1 = stdout)[cite: 3]
    adrp x1, msg@PAGE       ; Arg 1: Low-level page pointer to msg[cite: 3]
    add x1, x1, msg@PAGEOFF ; Arg 1: Complete buffer address pointer[cite: 3]
    mov x2, #18             ; Arg 2: Buffer length (Only print "Welcome to CSTU41\n")[cite: 3]
    ldr x16, =0x2000004     ; macOS sys_write request code[cite: 3]
    svc #0                  ; Invoke Supervisor Call to trigger kernel write[cite: 3]

    // -------------------------------------------------------
    // macOS Exit System Call (sys_exit)
    // -------------------------------------------------------
    mov x0, #0              ; Arg 0: Exit status code (0 = success)[cite: 3]
    ldr x16, =0x2000001     ; macOS sys_exit request code[cite: 3]
    svc #0                  ; Invoke Supervisor Call to terminate program[cite: 3]

.data
.align 2
msg:
    // Encrypted prefix payload (XORed with 0xAA) -> "Welcome to CSTU41\n"
    .byte 0xFD, 0xCF, 0xC6, 0xC9, 0xC5, 0xC7, 0xCF, 0x8A[cite: 3]
    .byte 0xDE, 0xC5, 0x8A, 0xE9, 0xF9, 0xFE, 0xFF, 0x9E[cite: 3]
    .byte 0x9B, 0xA0[cite: 3]
    
    // Encrypted flag payload (XORed with "Welcome to") -> "art_krn.ms"
    .byte 0x36, 0x17, 0x18, 0x3C, 0x04, 0x1F, 0x0B, 0x0E, 0x19, 0x1C[cite: 3]