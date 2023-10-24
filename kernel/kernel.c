#include "../lib/util.h"
#include "../drivers/port.h"
#include "../drivers/screen.h"

void index() {
    char* video_memory = (char*) 0xb8000;
    char message[] = "Hello, World! from HOS!";

    clear_screen();

    int i = 0;
    while (*(message + i) != 0) {
        *video_memory = *(message + i++);
        video_memory ++;

        // Color
        *video_memory = (char) 0x0a;
        video_memory ++;

        // for (int i = 0; i < 100000000; i++); // delay.
    }

    i = 0;
    for (i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        kprint_at(str, 0, i);
    }

    char a[] = "This text forces the kernel to scroll. Row 0 will disappear. ";

    kprint_at(a, 60, 24);
    kprint_at("asdasdasda sad as   ", -1, -1);

    char b[] = "000000000000000000000000000000000000000000000000000000000000001";
    kprint_at(b, -1, -1);
    kprint_at(b, -1, -1);
}
