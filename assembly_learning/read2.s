.global _start
.intel_syntax noprefix

_start:
    // input msg
    mov rax, 1
    mov rdi, 1
    lea rsi, [input_msg]
    mov rdx, 14
    syscall

    // input number as char
    mov rax, 0
    mov rdi, 1
    mov rdx, 2
    syscall

    // convert to number
    sub byte [rsi], '0'
    // increment by 1
    add byte [rsi], 1
    // convert back to char
    add byte [rsi], '0'

    mov byte [output_msg], sil

    // output result
    mov rax, 1
    mov rdi, 1
    lea rsi, [output_msg]
    mov rdx, 1
    syscall

    // sys_exit
    mov rax, 60
    xor edi, edi
    syscall

input_msg:
    .asciz "Input Number: "

output_msg:
    .byte 0
