rm_print:
    pusha
    mov ah, 0x0e

rm_print_start:
    mov al, [bx]

    cmp al, 0
    je rm_print_end

    int 0x10

    add bx, 1

    jmp rm_print_start

rm_print_end:
    mov ah, 0x0e

    mov al, 0x0a
    int 0x10

    mov al, 0x0d
    int 0x10
    popa
    ret

[bits 32]
pm_print:
    pusha
    mov edx, VIDEO_MEMORY

pm_print_start:
    mov al, [ebx]
    mov ah, COLOR

    cmp     al, 0
    je pm_print_end

    mov [edx], ax
    add ebx, 1
    add edx, 2

    jmp pm_print_start

pm_print_end:
    popa
    ret

VIDEO_MEMORY equ 0xb8000
COLOR equ 0x0f
