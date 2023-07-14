section .data
    message db "Enter a number: ", 0
    length equ $-message
    output_message db "Result: ", 0
    output_length equ $-output_message

section .bss
    input resb 16

section .text
    global _start

_start:
    ; Display message asking for input
    mov eax, 4
    mov ebx, 1
    mov ecx, message
    mov edx, length
    int 0x80

    ; Read user input
    mov eax, 3
    mov ebx, 0
    mov ecx, input
    mov edx, 16
    int 0x80

    ; Convert input to a number
    xor eax, eax
    xor ebx, ebx
    lea esi, [input]
convert_loop:
    cmp byte [esi], 0x0A  ; Check for newline character
    je convert_done
    imul eax, 10
    sub byte [esi], '0'
    add eax, dword [esi]
    inc esi
    jmp convert_loop
convert_done:

    ; Increment the number
    add eax, 1

    ; Convert the result back to a string
    xor ebx, ebx
    lea esi, [input]
convert_back_loop:
    xor edx, edx
    mov ecx, 10
    div ecx
    add edx, '0'
    dec esi
    mov [esi], dl
    test eax, eax
    jnz convert_back_loop

    ; Display the result message
    mov eax, 4
    mov ebx, 1
    mov ecx, output_message
    mov edx, output_length
    int 0x80

    ; Display the incremented number
    mov eax, 4
    mov ebx, 1
    lea ecx, [esi]
    mov edx, 16
    int 0x80

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80
