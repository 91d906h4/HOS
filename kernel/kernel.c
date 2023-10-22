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
}
