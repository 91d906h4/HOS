[bits 32]
[extern main]
    ; Call main function in kernel.c.
    call main

    jmp $
