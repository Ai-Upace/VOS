#pragma once
#ifndef PS2_H
#define PS2_H
#include <stdint.h>

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

int  getchar();
void update_cursor();
void putchar(const char c, const int color);
void kprintf(const char* s, const int color, ...);
int  strcmp(const char* s1, const char* s2);

struct KeyboardState {
    uint8_t modifiers; // Shift, Ctrl, Alt 等修饰键状态
    uint8_t lock; // Caps Lock, Num Lock 等锁定键状态
};

struct TextMode {

};

struct Full_Color {

};

#endif