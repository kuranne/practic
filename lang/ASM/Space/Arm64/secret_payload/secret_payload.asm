.global _main
.align 2

.text
_main:
    adrp x0, msg@PAGE       
    add x0, x0, msg@PAGEOFF 

    mov x1, #0              
    mov x2, #0xAA     

_stage1_loop
    ldrb w3, [x0, x1]       
    eor w3, w3, w2          
    strb w3, [x0, x1]       
    add x1, x1, #1          
    cmp x1, #18             
    b.ne _stage1_loop       
    mov x1, #0              

_stage2_loop:
    ldrb w2, [x0, x1]       
    add x3, x1, #18         
    ldrb w4, [x0, x3]       
    eor w4, w4, w2          
    strb w4, [x0, x3]       
    add x1, x1, #1          
    cmp x1, #10             
    b.ne _stage2_loop       
    mov x0, #1         

    adrp x1, msg@PAGE       
    add x1, x1, msg@PAGEOFF 
    mov x2, #18             
    ldr x16, =0x2000004     
    svc #0                  

    mov x0, #0              
    ldr x16, =0x2000001     
    svc #0                  
.data
.align 2
msg:
    .byte 0xFD, 0xCF, 0xC6, 0xC9, 0xC5, 0xC7, 0xCF, 0x8A ; 
    .byte 0xDE, 0xC5, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00 ; 
    .byte 0x00, 0xA0 ; 
    
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ; 