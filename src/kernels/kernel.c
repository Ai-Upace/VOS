#include "drivers/ps2.h"
#include "user/shell.h"

void main() {  
    puts("Visual Operating System - Professional Edition. Version 0.01\n", 0x07);
    puts("Copyright (c) by Ai-Upace.\n", 0x07);

    shell();

    // old: while (1);
    while (1) {
        asm volatile("hlt");
    }
}