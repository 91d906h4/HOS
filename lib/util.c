#include "util.h"

void mem_copy(char *source, char *dest, int n) {
    for (int i = 0; i < n; i++) {
        *(dest + i) = *(source + i);
    }
}

void int_to_ascii(int n, char str[]) {
    int sign, p = 0;

    if ((sign = n) < 0) n = -n;

    do str[p++] = n % 10 + 48; // '0' = 48.
    while ((n /= 10) > 0);

    if (sign < 0) str[p++] = '-';

    for (int i = 0; i < p >> 1; i++) {
        char temp = str[i];
        str[i] = str[p - i - 1];
        str[p - i - 1] = temp;
    }

    str[p] = '\0';
}