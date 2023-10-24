[org 0x7c00]
    jmp 0:boot

boot:
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax

    mov [BOOT_DRIVE], dl
    mov bp, 0x90000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call rm_print

    call load_kernel

    call switch_pm

    jmp $

%include "./boot/gdt.asm"
%include "./boot/disk.asm"
%include "./boot/print.asm"
%include "./boot/switch_pm.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call rm_print

    mov bx, KERNEL_OFFSET
    mov dh, 16
    mov dl, [BOOT_DRIVE]

    call disk_load
    ret

[bits 32]
pm_entry:
    mov ebx, MSG_PROT_MODE
    call pm_print

    call KERNEL_OFFSET

    jmp $

KERNEL_OFFSET equ 0x1000
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode...", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode...", 0
MSG_LOAD_KERNEL db "Loading kernel into memory...", 0

times 510-($-$$) db 0
dw 0xaa55
