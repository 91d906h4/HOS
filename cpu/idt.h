#ifndef _IDT_H
#define _IDT_H

#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

#include "../lib/util.h"
#include "../lib/types.h"

typedef struct {
    u16 low_offset;
    u16 sel;
    u8 _0;
    u8 flags; 
    u16 high_offset;
} __attribute__((__packed__)) idt_gate_t ;

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((__packed__)) idt_register_t;

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, u32 handler);
void set_idt();

#endif