#ifndef _UTIL_H
#define _UTIL_H

#include "./types.h"

void mem_copy(char* source, char* dest, int n);
void mem_set(u8* dest, u8 val, u32 n);
void int_to_ascii(int n, char str[]);

#endif