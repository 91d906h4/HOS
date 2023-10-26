[org 0x7c00]
    jmp 0:boot

boot:
    ; Clear registers.
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax

    mov [BOOT_DRIVE], dl
    mov bp, 0x90000
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call rm_print

    ; Load kernel.
    call load_kernel

    ; Switch to protected mode.
    call switch_pm

    jmp $

; Include modules.
%include "./boot/gdt.asm"
%include "./boot/disk.asm"
%include "./boot/print.asm"
%include "./boot/switch_pm.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call rm_print

    ; Store kernel in KERNEL_OFFSET (0x1000).
    mov bx, KERNEL_OFFSET
    ; Load 16 sectors in memory.
    mov dh, 16
    mov dl, [BOOT_DRIVE]

    ; Load kernel to disk.
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

times 510 - ($-$$) db 0
dw 0xaa55
