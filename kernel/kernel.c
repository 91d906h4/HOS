#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../lib/util.h"
#include "../drivers/port.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"

void main() {
    // Initialize ISR.
    init_isr();

    __asm__ __volatile__("sti");
    init_timer(50);

    init_keyboard();

    return;

    char* video_memory = (unsigned char*) 0xb8000;
    char message[] = "Hello, World! from HOS!";

    clear_screen();

    int i = 0;
    while (*(message + i) != 0) {
        *video_memory = *(message + i++);
        video_memory ++;

        // Color
        *video_memory = 0x0a;
        video_memory ++;

        // for (int i = 0; i < 100000000; i++); // delay.
    }

    i = 0;
    for (i = -240; i < 240; i++) {
        char str[255];
        int_to_ascii(i, str);
        kprint(str);
    }

    for (int i = 0; i < 10; i++) {
        for (int i = 0; i < 100000000; i++); // delay.

        kprint_at("This text forces the kernel to scroll.\tRow 0 will disappear. ", 60, 24);
    }
}