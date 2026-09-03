#set heading(numbering: "I.")
#set text(font: "New Computer Modern")
#show raw.where(block: true): block.with(
  fill: luma(250),
  inset: 10pt,
  radius: 4pt,
)

= The "Hello World" Programming

This will show how to write hello world in asm

```asm
.global main
.text
.section .rodata
  printf_fmt:
    .string "%s\n"
  hello_world:
    .string "Hello, World!" ; 13 + 1

.text
main:
  lea printf_fmt(%rip), %rdi
  lea hello_world(%rip), %rsi
  xor %eax, %eax
  call printf@PLT

  xor %rax, %rax
  ret
```