/*
 * Copyright (C) 2025 ~ ? Ai-Upace
 * Powered by Visual Operating System (VOS)
 * 
 * BY GPLv3 LICENSE:
 * - This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 
 * But if you want to shut down? No way! Please to
 * - Mental hospital
 * - FSF (Free Software Foundation)
 * - Court
 * 
 * - cn v :
 * 版权所有 (C) 2025 ~ ? Ai-Upace
 * 基于 VOS (Visual Operating System) 开发
 * 
 * 根据 GPLv3 许可证：
 * - 本程序是自由软件：您可以根据 GNU 通用公共许可证的条款重新分发和/或修改它
 * - 由自由软件基金会发布的 GNU 通用公共许可证
 * 
 * 但如果你想闭源？没门！请去;
 * - 精神病院
 * - 自由软件基金会 (FSF)
 * - 法院
 * 
 * END
 * <jntmngmhahayo@outlook.com>
 * <jntmngmhahayo@gmail.com>
 * 
 */
#include "include/drivers/ps2.h"
// Scancode to ASCII
char scancode_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x0
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',   // 0x10
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',           // 0x1E
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,             // 0x2C
    '*', 0, ' ', 0,                                                           // 0x36
    // more but future ...
};

char getchar() {  
    static int shift_pressed = 0;  
    while (1) {  
        // wait for a key press 
        while ((inb(0x64) & 0x01) == 0) asm("pause");  
        
        unsigned char scancode = inb(0x60);  
        
        // Skip release events and control keys 
        if (scancode & 0x80) continue;  
        if (scancode == 0x2A || scancode == 0x36) {  
            shift_pressed = 1;  
            continue;  
        }  
        if (scancode >= sizeof(scancode_ascii) || !scancode_ascii[scancode]) {  
            continue;  
        }  
        
        // Handle shift key release
        char c = scancode_ascii[scancode];  
        return (shift_pressed && c >= 'a' && c <= 'z') ? c - 32 : c;  
    }  
}

static int cursor_x = 0, cursor_y = 0;

void putchar(char c, int color) {
    volatile char *video = (volatile char*)VGA_ADDRESS;
    if (c == '\n') {
        cursor_x = 0; cursor_y++;
    } else {
        int pos = 2 * (cursor_y * VGA_WIDTH + cursor_x);
        video[pos] = c;
        video[pos+1] = color; // function color (in 'void putchar(char c, int color)' --> int color)
        cursor_x++;
    }
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0; cursor_y++;
    }
    if (cursor_y >= VGA_HEIGHT) {
        cursor_y = 0; // or scroll up, etc.
    }
}

void puts(const char* s, int color, ...) { 
    while (*s) putchar(*s++, color); 
}

