#include "drivers/ps2.h"
#include "user/shell.h"

void main() {
    // Visual Operating System - Professional Edition
    kprintf("Visual-DOS - Professional Edition. Version 0.01\n", 0x07);
    kprintf("Copyright (c) 2025 by Ai-Upace.\n", 0x07);

    kprintf("%c%c%c%c\n", 0x07, 0,0,0,0); // test

    // or

    kprintf("%s", 0x07, "Hello, world!\n");

    shell();

    // old: while (1);
    while (1) {
        asm volatile("hlt");
    }
}