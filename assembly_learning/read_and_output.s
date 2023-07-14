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

    // mov sil, byte [rsi]

    // convert to number
    // sub rsi, '0'
    // increment by 1
    //add rsi, 1
    // convert back to char
    // add rsi, '0'

    // test 1 output
    // mov rax, 1
    // mov rdi, 1
    // lea rsi, [msg]
    // mov rdx, 7
    // syscall

    // mov byte [output_msg], sil
    // mov [output_msg], sil

    // Test 2 output
    // mov rax, 1
    // mov rdi, 1
    // lea rsi, [msg2]
    // mov rdx, 7
   //  syscall

    // output result
    mov rax, 1
    mov rdi, 1
    lea rsi, [rsi]
    mov rdx, 100
    syscall

    // sys_exit
    mov rax, 60
    mov rdi, 69
    syscall

input_msg:
    .asciz "Input Number: "

msg:
    .asciz "Test 1\n"

msg2:
    .asciz "Test 2\n"

output_msg:
    .space 1
