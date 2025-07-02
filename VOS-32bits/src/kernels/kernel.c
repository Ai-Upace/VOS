#include "drivers/ps2.h"
#include "user/shell.h"

void main() {  
    puts("Visual Operating System - Professional Edition. Version 0.01\n", 0x07);
    puts("Copyright (c) by Ai-Upace.\n", 0x07);

    puts("%c%c%c%c\n", 0x07, 0,0,0,0); // test

    // or

    puts("%s", 0x07, "Hello, world!\n");

    shell();

    // old: while (1);
    while (1) {
        asm volatile("hlt");
    }
}